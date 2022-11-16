/*!*************************************************************************
****
\file LevelEditor.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-9-2022
\brief  This program utilises Dear ImGui and OpenGL to create a editor interface
        to allow us to edit object, create entities and modify the
        properties of the components and save them accordingly.
****************************************************************************
***/
#include "empch.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/ImGuizmo.h>

#include "LevelEditor.h"
#include "ExoEngine/Timer/Time.h"
#include "ExoEngine/Timer/Fps.h"
#include "Platform/Graphics/Renderer.h"

#include "Platform/Graphics/FrameBuffer.h"
#include "ExoEngine/Log.h"
#include "ExoEngine/Audio/AudioEngine.h"

#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/Log.h"
#include "ExoEngine/ECS/Components/Components.h"
#include <glm/gtc/type_ptr.hpp>

namespace EM {

    std::unique_ptr<LevelEditor> LevelEditor::m_instance{ nullptr };

    std::unique_ptr<LevelEditor>& LevelEditor::GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = std::make_unique<LevelEditor>();
        }
        return m_instance;
    }

    bool color_picker = false;
    bool drop_menu = false;
    bool logger = false;
    
    static int current_sound = 0;

    // Init for levelEditor sets context for ImGui 
    void LevelEditor::Init(Window* window)
    {
        m_window = window;
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 450");
    }

    //  Update loop for level editor, poll events and set new frames
    void LevelEditor::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        Docking();
        MainMenuBar();
        Profiler();
        ImGui::ShowDemoWindow();
        ContentBrowser();
        Logger();
        Hierarchy();
        Inspector();
        SceneViewer();
        Audio();
    }
    //  Render interface onto frame

    void LevelEditor::Draw()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            auto* mWindow = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(mWindow);
        }

    }

    //  End instance
    void LevelEditor::End()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    //Menu bar located in the top left side of the window is used to toggle between opening and closing the editor
    void LevelEditor::MainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Editor Control"))
            {
                if (ImGui::MenuItem("Open"))
                {
                    show_window = true;
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Close"))
                {
                    show_window = false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void LevelEditor::SceneViewer()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Scene");
       
        float tab_size = (ImGui::GetWindowSize().y - ImGui::GetContentRegionAvail().y) * 2;
        ImVec2 position = ImGui::GetWindowPos();
        ImVec2 size = ImGui::GetContentRegionAvail();
        camera.Resize(size.x, size.y);
        //camera.MouseScrolling();
        
        ImVec2 offset{
           position.x - (mwindata.GetWidth() - position.x - size.x) + (ImGui::GetContentRegionAvail().x - size.x),
           position.y - (mwindata.GetHeight() - position.y - size.y) + (ImGui::GetContentRegionAvail().y - size.y) + tab_size
        };

        _gameWindowSpecs = {
            position.x + 0.5f * (ImGui::GetContentRegionAvail().x - size.x),
            position.y + 0.5f * (ImGui::GetContentRegionAvail().y - size.y + tab_size),
            size.x,
            size.y
        };

        unsigned int textureID = p_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)(intptr_t)textureID, ImGui::GetContentRegionAvail(),
            ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        
        //gizmos
        mGizmoType = ImGuizmo::OPERATION::TRANSLATE; // for now just having translation for guizmo
        ImGuizmo::BeginFrame();
        if (selectedEntity >= 0 && p_ecs.HaveComponent<Transform>(selectedEntity))//have selected entity
        {
            ImGuizmo::SetOrthographic(true);
            
   

            ImGuizmo::SetRect(
                _gameWindowSpecs.x,
                _gameWindowSpecs.y,
                _gameWindowSpecs.z,
                _gameWindowSpecs.w
            );

            glm::mat4 cameraProj = camera.GetProjectionMatrix();
            glm::mat4 cameraView = camera.GetViewMatrix();
            //std::cout << cameraView[0].x << std::endl;
            glm::mat4 transform{ 1.0f }; // identity matrix

            auto& trans = p_ecs.GetComponent<Transform>(selectedEntity);

            transform = glm::translate(glm::mat4{ 1.0f },glm::vec3(trans.GetPos().x, trans.GetPos().y, 0.0f))
                * glm::rotate(glm::mat4(1.f), trans.GetRot(), glm::vec3(0.f, 0.f, 1.f))
                * glm::scale(glm::mat4(1.f), { trans.GetScale().x,trans.GetScale().y ,1.f });

            ImGuizmo::SetDrawlist();
            // Draw ImGuizmo (renders every frame)
            ImGuizmo::Manipulate(glm::value_ptr(glm::inverse(transform))
                , glm::value_ptr(cameraProj), (ImGuizmo::OPERATION)mGizmoType,
                ImGuizmo::WORLD, glm::value_ptr(transform));

            if (ImGuizmo::IsUsing())
            {
                float decompTrans[3], decompRot[3], decompScale[3];

                ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), decompTrans, decompRot, decompScale);
                // change size 
                trans.SetPos(decompTrans[0], decompTrans[1]);
            }
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    // Content browser to be implemented in M3
    void LevelEditor::ContentBrowser()
    {
      ImGui::Begin("Content Browser");
      if (m_CurrentDirectory != std::filesystem::path(mAssetsPath))
      {
          if (ImGui::ImageButton((void*)(intptr_t)ResourceManager::GetIcon("BackIcon")->GetRendererID(),
                  { 25.f,25.f }, { 0, 1 }, { 1, 0 }))
          {
              m_CurrentDirectory = m_CurrentDirectory.parent_path();
          }
      }

      for (auto& Directory : std::filesystem::directory_iterator(m_CurrentDirectory))
      {
          const auto& directorypath = Directory.path(); //the path for folders in Assets(assets/fonts)
        
          std::string filename = directorypath.filename().string(); //just the name of the folders(fonts, icons, metadigger etc)
          ImGui::PushID(filename.c_str());
          ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
          
          if (Directory.is_directory())
          {
              ImGui::ImageButton((void*)(intptr_t)ResourceManager::GetIcon("FolderIcon")->GetRendererID(),
                  { 128.f,128.f }, { 0, 1 }, { 1, 0 });
          }
      
          //Press into the folder
          ImGui::PopStyleColor();
          if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
          {
              if (Directory.is_directory())
                  m_CurrentDirectory /= directorypath.filename();
          }
          
          ImGui::TextWrapped(filename.c_str()); ImGui::NextColumn(); //indicate the folder name
          ImGui::PopID();   
      }
      
      ImGui::End();

      ImGui::Begin(m_CurrentDirectory.filename().string().c_str(),(bool*)0, ImGuiWindowFlags_HorizontalScrollbar);
      if (m_CurrentDirectory.filename() == "Textures")
      {
          for (auto& [name, texObj] : ResourceManager::textures)
          {
              ImGui::Image((void*)(intptr_t)texObj->GetRendererID(),
                  ImVec2(128 * static_cast<float>(texObj->GetWidth()) / static_cast<float>(texObj->GetHeight()), 128),
                  ImVec2(0.0f, 1.0f),
                  ImVec2(1.0f, 0.0f));

              if (ImGui::IsItemHovered())
              {
                  ImGui::BeginTooltip();
                  std::string str = name + " " + "(" + std::to_string(texObj->GetWidth()) + "x" + 
                                    std::to_string(texObj->GetHeight()) + ")";
                  ImGui::Text(str.c_str());
                  ImGui::EndTooltip();
              }

              if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
              {
                  ImGui::SetDragDropPayload("Textures", &name, sizeof(name));
                  ImGui::Image((void*)(intptr_t)texObj->GetRendererID(),
                      ImVec2(128* static_cast<float>(texObj->GetWidth()) / static_cast<float>(texObj->GetHeight()), 128),
                      ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
                  ImGui::EndDragDropSource();
              }
          }
      }
      else if (m_CurrentDirectory.filename() == "Icons")
      {
          for (auto& [name, texObj] : ResourceManager::Icons)
          {
              ImGui::SameLine();
              ImGui::Image((void*)(intptr_t)texObj->GetRendererID(),
                  ImVec2(128 * static_cast<float>(texObj->GetWidth()) / static_cast<float>(texObj->GetHeight()), 128),
                  ImVec2(0.0f, 1.0f),
                  ImVec2(1.0f, 0.0f));

              if (ImGui::IsItemHovered())
              {
                  ImGui::BeginTooltip();
                  std::string str = name + " " + "(" + std::to_string(texObj->GetWidth()) + "x" +
                      std::to_string(texObj->GetHeight()) + ")";
                  ImGui::Text(str.c_str());
                  ImGui::EndTooltip();
              }
          }

      }
      ImGui::End();

    }

    // Logger, can toggle between types of messages you want to view
    void LevelEditor::Logger()
    {
        if (show_window)
        {

            if (ImGui::Begin("Logger"))
            {
                static bool info = true;
                ImGui::Checkbox("Info       ", &info);

                ImGui::SameLine();

                static bool warning = true;
                ImGui::Checkbox("warning    ", &warning);

                ImGui::SameLine();

                static bool error = true;
                ImGui::Checkbox("error", &error);

                static bool system = true;
                ImGui::Checkbox("system     ", &system);

                ImGui::SameLine();

                static bool log = true;
                ImGui::Checkbox("log        ", &log);

                ImGui::SameLine();

                static bool fatal = true;
                ImGui::Checkbox("fatal", &fatal);

                if (info)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                    ImGui::Text(Log::GetImguiLog().c_str());
                    ImGui::PopStyleColor();

                    if (current_sound > 0)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                        ImGui::Text("Audio Channel %d is played", current_sound);
                        ImGui::PopStyleColor();
                    }
                    
                }

                if (warning)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
                    ImGui::Text("This is an Warning Message");
                    ImGui::PopStyleColor();
                }

                if (error)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                    ImGui::Text("This is an Error Message");
                    ImGui::PopStyleColor();
                }

                if (system)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(52, 67, 235, 255));
                    ImGui::Text("This is an System Message");
                    ImGui::PopStyleColor();
                }

                if (log)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(52, 222, 235, 255));
                    ImGui::Text("This is an Log Message");
                    ImGui::PopStyleColor();
                }

                if (fatal)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                    ImGui::Text("This is an Fatal Message");
                    ImGui::PopStyleColor();
                }
            }
            ImGui::End();
        }
    }

    //Docking allows us to dock the ImGui windows to the edges of the scene
    void LevelEditor::Docking()
    {
        //Set docking flags
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", 0, window_flags);

        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::End();

    }

    /*
    Profiler displays information about the users system such as 
    
    Renderer and version of renderer (GPU)

    FPS
    
    Rendered info e.g. Quads, vertices, indices drawn etc.

    */
    void LevelEditor::Profiler()
    {
        if (show_window)
        {
            ImGui::Begin("Profiler");
            //Opengl information
            ImGui::Text("Opengl Information ");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("Version: %s", glGetString(GL_VERSION));
            ImGui::Text("\n");

            // how much time per frame and Fps
            ImGui::Text("Application average % .3f ms / frame(% .3f FPS)", 1000.0f / FramePerSec::GetInstance().GetFps(), FramePerSec::GetInstance().GetFps());

            //Renderering Information
            ImGui::Text("\n");
            auto Infos = Renderer::GetInfo();
            ImGui::Text("Renderer Information");
            ImGui::Text("Draw Calls: %d", Infos.n_DrawCalls);
            ImGui::Text("Quads: %d", Infos.n_Quad);
            ImGui::Text("Vertices: %d", Infos.TotalVertexUsed());
            ImGui::Text("Indices: %d", Infos.TotalIndexUsed());

            ImGui::Checkbox("Show physics colliders", &mDebugDraw);

            //Todo show the each system consume how much at runtime
            mSystemRunTime[0] = Timer::GetInstance().GetDT(Systems::COLLISION)/ Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[1] = Timer::GetInstance().GetDT(Systems::GRAPHIC)/ Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[2] = Timer::GetInstance().GetDT(Systems::PHYSICS)/ Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[3] = Timer::GetInstance().GetDT(Systems::LOGIC)/ Timer::GetInstance().GetGlobalDT();
            mSystemRunTime[4] = Timer::GetInstance().GetDT(Systems::API)/ Timer::GetInstance().GetGlobalDT();

            ImGui::Text("COLLISION");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[0], ImVec2(-1.0f, 0.0f));
            ImGui::Text("GRAPHIC");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[1], ImVec2(-1.0f, 0.0f));
            ImGui::Text("PHYSICS");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[2], ImVec2(-1.0f, 0.0f));
            ImGui::Text("LOGIC");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[3], ImVec2(-1.0f, 0.0f));
            ImGui::Text("API");
            ImGui::SameLine(80);
            ImGui::ProgressBar(mSystemRunTime[4], ImVec2(-1.0f, 0.0f));

            ImGui::End();

         
        }
    }

    // Create, destroy and clone entities
    void LevelEditor::Hierarchy()
    {
        ImGui::Begin("Hierarchy");
        if (ImGui::Button("Create Entity") && p_ecs.GetTotalEntities() != MAX_ENTITIES)
        {  
            p_ecs.AddComponent<NameTag>(p_ecs.CreateEntity(), NameTagComponent);
        }

        if (p_ecs.GetTotalEntities() > 0)
        {
            ImGui::SameLine();
            if (ImGui::Button("Destroy Entity"))
            {
                if (selectedEntity != MAX_ENTITIES)
                {
                    p_ecs.DestroyEntity(selectedEntity);
                }
                //selectedEntity = {}; // when the entity is destroy there is no current selected entity
            }
            ImGui::SameLine();
            if (ImGui::Button("Clone Entity") && p_ecs.GetTotalEntities() != 0)// there is entity alive
            {
                if (selectedEntity != MAX_ENTITIES)
                {
                    Entity CloneEntity = p_ecs.CloneEntity(selectedEntity);
                    selectedEntity = CloneEntity; // when the entity is destroy there is no current selected entity
                }
            }
            
            auto aliveTotal = p_ecs.GetTotalEntities();
            Entity aliveCount = 0;
            Entity iterEntity = 0;
            while (aliveCount < aliveTotal)
            { 
                if (p_ecs.HaveComponent<NameTag>(iterEntity))
                {
                    const auto& tag = p_ecs.GetComponent<NameTag>(iterEntity).GetNameTag();

                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow;
                    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)iterEntity, flags, tag.c_str());

                    if (ImGui::IsItemClicked())
                        selectedEntity = iterEntity;

                    if (opened)
                        ImGui::TreePop();

                    aliveCount++;
                }

                iterEntity++;
            }
        }

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            selectedEntity = {};
        ImGui::End();

    }

    //Inspector allows us to manipulate the entity properties, modifying scale, rotation and position of the object.
    void LevelEditor::Inspector()
    {
        ImGui::Begin("Inspector");
        if (selectedEntity != MAX_ENTITIES)// if the selectedEntityExist
        {
            //create component for the selected entity 
            if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("Add Component");

            if (ImGui::BeginPopup("Add Component"))
            {
                
                if (ImGui::MenuItem("Transform"))
                {
                    if(!p_ecs.HaveComponent<Transform>(selectedEntity))
                        p_ecs.AddComponent<Transform>(selectedEntity, TransformComponent);
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sprite"))
                {
                    if (!p_ecs.HaveComponent<Sprite>(selectedEntity))
                    p_ecs.AddComponent<Sprite>(selectedEntity, SpriteComponent);
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Collider"))
                {
                    p_ecs.AddComponent<Collider>(selectedEntity, ColliderComponent);
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("RigidBody"))
                {
                    p_ecs.AddComponent<RigidBody>(selectedEntity, RigidBodyComponent);
                    ImGui::CloseCurrentPopup();
                }
                
                ImGui::EndPopup();
            }
            //Check and change the name of the Entity
            if (p_ecs.HaveComponent<NameTag>(selectedEntity))
            {
                if (ImGui::CollapsingHeader("Name", ImGuiTreeNodeFlags_None))
                {
                    auto& name = p_ecs.GetComponent<NameTag>(selectedEntity).GetNameTag();
                    char buffer[256];
                    memset(buffer, 0, sizeof(buffer));
                    strcpy_s(buffer, sizeof(buffer), name.c_str());
                    if (ImGui::InputText("name", buffer, sizeof(buffer)))
                    {
                        name = std::string(buffer);
                    }
                 }
             }
            //If Entity have Transform Component
            if (p_ecs.HaveComponent<Transform>(selectedEntity))
            {
                if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_None))
                {
                    //position
                    auto& Position = p_ecs.GetComponent<Transform>(selectedEntity).GetPos();
                    ImGui::PushItemWidth(100.0f);
                    ImGui::Text("Position"); ImGui::SameLine();
                    ImGui::Text("X"); ImGui::SameLine();                    //set a "x" to indicate x-axis
                    ImGui::DragFloat("##Position", (float*)&Position.x, 0.005f); ImGui::SameLine(); //char name , pass float pointer to position vec2D which hold x and y, the scaling value in imgui
                    ImGui::PushID(1);
                    ImGui::Text("Y"); ImGui::SameLine();
                    ImGui::DragFloat("##Position", (float*)&Position.y, 0.005f);
                    ImGui::PopID();

                    //scale
                    auto& Scale = p_ecs.GetComponent<Transform>(selectedEntity).GetScale();
                    ImGui::Text("Scale   "); ImGui::SameLine();
                    ImGui::Text("X"); ImGui::SameLine();                    //set a "x" to indicate x-axis
                    ImGui::DragFloat("##Scale", (float*)&Scale.x, 0.005f); ImGui::SameLine(); //char name , pass float pointer to position vec2D which hold x and y, the scaling value in imgui
                    ImGui::PushID(2);
                    ImGui::Text("Y"); ImGui::SameLine();
                    ImGui::DragFloat("##Scale", (float*)&Scale.y, 0.005f);
                    ImGui::PopID();
                    //EM_EXO_INFO("Scale(x:{0}, y:{1})", Scale.x, Scale.y);

                    //rotation
                    auto& rotation = p_ecs.GetComponent<Transform>(selectedEntity).GetRot();
                    ImGui::Text("Rotation Z"); ImGui::SameLine();
                    ImGui::DragFloat("##", (float*)&rotation, 1.0f);
                    //EM_EXO_INFO("Rotation(z:{0})", rotation);
                }
            }
            //Sprite Component
            if (p_ecs.HaveComponent<Sprite>(selectedEntity))
            {
                
                if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_None))
                {
                    auto& sprite = p_ecs.GetComponent<Sprite>(selectedEntity);
                    ImGui::Checkbox("SpriteSheet", &sprite.mIsSpriteSheet);
                    ImGui::Checkbox("Animation", &sprite.mIsanimated);
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4());
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4());
                    ImGui::Button("Image : "); ImGui::SameLine(80.0f);
                    ImGui::PopStyleColor(3);
                    auto& texturePath = p_ecs.GetComponent<Sprite>(selectedEntity).GetTexture();
                    ImGui::SetNextItemWidth(140.0f);

                    if (ImGui::BeginCombo("##sprite", texturePath.c_str()))
                    {
                        for (auto& [str, tex] : ResourceManager::textures)
                        {
                            if (ImGui::Selectable(str.c_str()))
                            {
                                texturePath = str;
                                EM_EXO_INFO("Loaded {0} Sprite", texturePath.c_str());
                            }
                        }
                        ImGui::EndCombo();
                    }

                }
            }
            //Collider Component
            if (p_ecs.HaveComponent<Collider>(selectedEntity))
            {
                if (ImGui::CollapsingHeader("Collider", ImGuiTreeNodeFlags_None))
                {
                    auto& collider = p_ecs.GetComponent<Collider>(selectedEntity).GetCollider();
                    //if(ImGui::BeginChild())

                    int colliderIndex = static_cast<int>(collider);
                    const char* colliderNames = "none\0circle\0line\0rect";
                    ImGui::Text("Collider Type"); ImGui::SameLine();
                    ImGui::Combo("##test", &colliderIndex, colliderNames);
                    collider = static_cast<Collider::ColliderType>(colliderIndex);
                }
            }
            //Rigid Component
            if (p_ecs.HaveComponent<RigidBody>(selectedEntity))
            {
                if (ImGui::CollapsingHeader("RigidBody", ImGuiTreeNodeFlags_None))
                {
                    //velocity
                    auto& velocity = p_ecs.GetComponent<RigidBody>(selectedEntity).GetVel();
                    ImGui::PushItemWidth(100.0f);
                    ImGui::Text("Velocity   "); ImGui::SameLine();
                    ImGui::Text("X"); ImGui::SameLine();
                    ImGui::DragFloat("##Velocity", (float*)&velocity.x, 0.005f); ImGui::SameLine();
                    ImGui::PushID(3);
                    ImGui::Text("Y"); ImGui::SameLine();
                    ImGui::DragFloat("##Velocity", (float*)&velocity.y, 0.005f);
                    ImGui::PopID();

                    //Direction
                    auto& direction = p_ecs.GetComponent<RigidBody>(selectedEntity).GetDir();
                    ImGui::PushItemWidth(100.0f);
                    ImGui::Text("Direction  "); ImGui::SameLine();
                    ImGui::Text("X"); ImGui::SameLine();
                    ImGui::DragFloat("##Direction", (float*)&direction.x, 0.005f); ImGui::SameLine();
                    ImGui::PushID(4);
                    ImGui::Text("Y"); ImGui::SameLine();
                    ImGui::DragFloat("##Direction", (float*)&direction.y, 0.005f);
                    ImGui::PopID();

                    //GetFricition
                    auto& friction = p_ecs.GetComponent<RigidBody>(selectedEntity).GetFriction();
                    ImGui::Text("Friction   "); ImGui::SameLine();
                    ImGui::DragFloat("##Friction", (float*)&friction, 1.0f);

                    //GetRestitution
                    auto& Restitution = p_ecs.GetComponent<RigidBody>(selectedEntity).GetRestitution();
                    ImGui::Text("Restitution"); ImGui::SameLine();
                    ImGui::DragFloat("##Restitution", (float*)&Restitution, 1.0f);
                }
            }
        if (ImGui::Button("Delete Component"))
              ImGui::OpenPopup("Delete Component");

        if (ImGui::BeginPopup("Delete Component"))
        {
            if (ImGui::MenuItem("Transform") && p_ecs.HaveComponent<Transform>(selectedEntity))
            {
                p_ecs.RemoveComponent<Transform>(selectedEntity);
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::MenuItem("Sprite") && p_ecs.HaveComponent<Sprite>(selectedEntity))
            {
                p_ecs.RemoveComponent<Sprite>(selectedEntity);
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::MenuItem("Collider") && p_ecs.HaveComponent<Collider>(selectedEntity))
            {
                p_ecs.RemoveComponent<Collider>(selectedEntity);
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::MenuItem("RigidBody") && p_ecs.HaveComponent<RigidBody>(selectedEntity))
            {
                p_ecs.RemoveComponent<RigidBody>(selectedEntity);
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
    ImGui::End();

    }

   

    //Audio manager allows users to select and play and test different audios in the editor
    //Need to shift loading of audio files into asset manager in M3
    void LevelEditor::Audio()
    {
        if (show_window)
        {
            ImGui::Begin("Audio Manager");
            
            //auto& AudioPath = p_ecs.GetComponent<Audio>()
            const char* items[] = { "FStep1", "FStep2", "FStep3", "FStep4", "FStep5", "Whoosh1", "Whoosh2", "Whoosh3", "Whoosh4", "Whoosh5", "test" };
            static int item_current = 0;
            static const char* current_item = NULL;

            ImGui::Combo("Load Sound", &item_current, items, IM_ARRAYSIZE(items));

            static int play_clicked = 0;
            static int stop_clicked = 0;

            //play audio file based on sound selected 
            if (ImGui::Button("Play Sound"))
                play_clicked++;

            if ((play_clicked & 1) && item_current == 0)
            {
                
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                current_sound = p_Audio->PlaySound("Assets/metadigger/FStep1.wav", 50.f); 
                play_clicked = 0;
            }
            /*std::string filePath = "";
            p_Audio->Loadsound(filePath);*/
            if ((play_clicked & 1) && item_current == 1)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                current_sound = p_Audio->PlaySound("Assets/metadigger/FStep2.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 2)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/FStep3.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 3)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/FStep4.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 4)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/FStep5.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 5)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/Whoosh1.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 6)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/Whoosh2.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 7)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/Whoosh3.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 8)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/Whoosh4.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 9)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                p_Audio->PlaySound("Assets/metadigger/Whoosh5.wav", 50.f);
                play_clicked = 0;
            }

            if ((play_clicked & 1) && item_current == 10)
            {
                ImGui::SameLine();
                ImGui::Text("Playing!");
                stop_clicked = 0;
                current_sound = p_Audio->PlaySound("Assets/metadigger/test.wav", 50.f);
                play_clicked = 0;
            }
            //pause audio file based on sound selected 
            if (ImGui::Button("Pause Sound"))
                stop_clicked++;

            if (stop_clicked & 1)
            {
                ImGui::SameLine();
                ImGui::Text("Paused!");
                play_clicked = 0;
                //p_Audio->Release();
               p_Audio->PauseSound(current_sound);
            }

            //set voulume slider
            static float f1 = 0.0f;
            ImGui::SliderFloat("Set Volume", &f1, 0.0f, 1.0f, "Max - Min %.3f");
            p_Audio->SetVolume(current_sound, f1);
            ImGui::End();

        }
    }
}
