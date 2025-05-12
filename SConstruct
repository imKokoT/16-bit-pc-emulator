import os


ON = '1'
OFF = '0'

# --- PROJECT SETTINGS ----------------------------------------------------------------------------
OUTPUT_NAME = 'emulator'

# --- OPTIONS -------------------------------------------------------------------------------------
debug = ARGUMENTS.get('debug', OFF) == ON
optimize = ARGUMENTS.get('debug', OFF) == ON  # only release


# --- CREATE ENVIRONMENT --------------------------------------------------------------------------
if debug:
    env = Environment(
        tools=['default', 'msvc'],
        CXXFLAGS=['/std:c++17', '/EHsc', '/Zi', '/FS'],  # /Zi: debug info
        LINKFLAGS=['/DEBUG']  # generate .pdb files
    )
else:
    flags = ['/std:c++17']
    if optimize: flags.append('/O2')

    env = Environment(
        tools=['default', 'msvc'],
        CXX='cl',
        CXXFLAGS=flags    
    )


# --- SCAN SOURCES --------------------------------------------------------------------------------
src = Glob('src/*.cpp')
obj = []
for src in src:
    op = os.path.join('build', 'obj', os.path.splitext(os.path.basename(str(src)))[0] + '.o')
    o = env.Object(target=op, source=src)
    obj.append(o)

# --- BUILD ---------------------------------------------------------------------------------------
if debug:
    env.Program(target=f'build/bin/{OUTPUT_NAME}-debug', source=obj)
else:
    env.Program(target=f'build/bin/{OUTPUT_NAME}', source=obj)
