from distutils.core import setup, Extension

spawn_module = Extension('_spawn', sources=['module/spawnmodule.c'])

setup(name='pySpawn',
      version='0.1.0',
      description='Python library to create child processes and send STDIN and capture STDOUT ',
      ext_modules=[spawn_module],
      long_description=open("README.md").read(),
      author="Levi Bostian",
      author_email="levi.bostian@gmail.com",
      url="https://github.com/levibostian/pySpawn",
      license="MIT",
      keywords="pyspawn child process")
