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
      packages=["pyspawn"],
      keywords="pyspawn child process",
      install_requires=['sphinx_rtd_theme==0.1.6', 'Sphinx==1.2.3', 'sphinx-autobuild==0.3.0'])
