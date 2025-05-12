import os

env = Environment(
    tools=['default', 'msvc'],
    CXX='cl',
    CXXFLAGS=['/std:c++17']
)

src_files = Glob('src/*.cpp')
obj_files = []
for src in src_files:
    # src: e.g., 'src/main.cpp' → 'build/obj/main.o'
    obj_path = os.path.join('build', 'obj', os.path.splitext(os.path.basename(str(src)))[0] + '.o')
    obj = env.Object(target=obj_path, source=src)
    obj_files.append(obj)

# building
env.Program(target='build/bin/emulator', source=obj_files)
