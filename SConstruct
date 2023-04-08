#!/usr/bin/env python
import os
import sys

# Initialize environment to Godot defaults
env = SConscript("thirdparty/godot-cpp/SConstruct")

# Project source files
sources = Glob("src/*.cpp")

# Header includes
env.Append(CPPPATH=[
    "src/",
    "thirdparty/mediapipe_cpp_lib/src",
    "thirdparty/mediapipe_cpp_lib/import_files",
    "thirdparty/protobuf/src"
])

if env["platform"] == "windows":
    # Add MediaPipeCppLib library
    env.Append(LIBPATH=["thirdparty/mediapipe_cpp_lib/mediapipe/bazel-out/x64_windows-opt/bin/cpp_library"])
    env.Append(LIBS=["gmod.if"])

    # Add Protobuf library
    env.Append(LIBPATH=["thirdparty/mediapipe_cpp_lib/mediapipe/bazel-out/x64_windows-opt/bin/external/com_google_protobuf"])
    env.Append(LIBS=["protobuf_lite.lo"])

# Shared library target
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "project/addons/pipedoll/libpipedoll.{}.{}.framework/libpipedoll.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    env["PDB"] = "project/addons/pipedoll/bin/libpipedoll{}{}.pdb".format(env["suffix"], env["SHLIBSUFFIX"]),
    library = env.SharedLibrary(
        "project/addons/pipedoll/bin/libpipedoll{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
