#include "Menu.h"

Menu::Menu(GLFWwindow* window) {
	const char* glsl_version = "#version 330";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

Menu::~Menu() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Menu::show() const {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Menu");
	
	  ImGui::Text("1.Camera");
	  ImGui::RadioButton("Freeze", &imgui_view, IMGUI_VIEW_FREEZE); ImGui::SameLine();
	  ImGui::RadioButton("Move", &imgui_view, IMGUI_VIEW_MOVE);
	  ImGui::Text("2.Shadow");
	  ImGui::RadioButton("Disable", &shadow_show, WITHOUT_SHADOW ); ImGui::SameLine();
	  ImGui::RadioButton("Enable", &shadow_show, WITH_SHADOW);
	  ImGui::Text("3.Particle System");
	  ImGui::RadioButton("Disable", &particle_show, WITHOUT_PARTICLE ); ImGui::SameLine();
	  ImGui::RadioButton("Enable", &particle_show, WITH_PARTICLE);
	  ImGui::Text("4.Stencil Test");
	  ImGui::RadioButton("Disable", &stencil_show, WITHOUT_STENCIL); ImGui::SameLine();
	  ImGui::RadioButton("Enable", &stencil_show, WITH_STENCIL);
	  ImGui::Text("5.Blood Locking");
	  ImGui::RadioButton("Disable", &blood_lock, BLOOD_LOOSE); ImGui::SameLine();
	  ImGui::RadioButton("Enable", &blood_lock, BLOOD_LOCK);
	  
	  ImGui::Text("Time Rate");
	  ImGui::SliderFloat(" ", &time_rate, 1.0, 10.0);


	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}