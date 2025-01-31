#pragma once

#include <godot_cpp/variant/string.hpp>

using namespace godot;

class SandboxProjectSettings {
public:
	static void register_settings();

	static bool use_global_sandbox_names();

	static bool get_docker_enabled();

	static String get_docker_path();

	static bool async_compilation();

	static bool use_native_types();

	static bool debug_info();

	static Array get_global_defines();
};
