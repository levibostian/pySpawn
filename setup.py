from distutils.core import setup, Extension
from src import version

spawn_module = Extension('spawn', sources = ['module/spawnmodule.c']) 

setup (name = 'pySpawn',
       version = version.get_version(),
       description = 'Python library to create child processes and send STDIN and capture STDOUT ',
       ext_modules = [spawn_module],
       long_description=open("README.md").read(),
       author="Levi Bostian",
       author_email="levi.bostian@gmail.com",
       url="https://github.com/levibostian/pySpawn",
       license="MIT",
       keywords = "pyspawn child process",
       packages=["pyspawn"],
       entry_points={"console_scripts": ["pyspawn = src.pyspawn:main"]},
       install_requires=['docopt==0.6.1'])
