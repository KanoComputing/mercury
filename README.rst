============
Introduction
============

.. image:: https://www.codefactor.io/repository/github/kanocomputing/mercury/badge
   :target: https://www.codefactor.io/repository/github/kanocomputing/mercury
   :alt: CodeFactor

Mercury provides a cross-platform base layer for configuring the system.


Etymology
=========

"Why Mercury?" I hear you say. Primarily because `Mercury <https://en.wikipedia.org/wiki/Mercury_(mythology)>`_ was the Roman god of boundaries, communication and travel which aligns with this project's main goals:

* Boundaries: Project Mercury will form the boundary between hardware and what a consumer wants to do, abstracting away platform-specifics.
* Communication: Project Mercury provides a translation abstraction layer between the consumers and the base hardware, regardless of what that may be.
* Travel: Project Mercury is designed to be cross-platform from the beginning, allowing the same apps to be delivered across multiple different platforms by providing the base abstraction upon which all functionality can be leveraged.

Additionally, `Project Mercury <https://en.wikipedia.org/wiki/Project_Mercury>`_ was the first United States human spaceflight program and likewise this is our first foray into colonising other planets (well, hardware).

Finally, `Mercury <https://en.wikipedia.org/wiki/Mercury_(element)>`_ is an element known to send people mad when they inhale too much of the fumes: hopefully not a sign of things to come with this project.

===============
Getting Started
===============

The technologies which are used in this project are:

.. code:: bash

   c++11
   cmake
   conan
   cpplint
   doxygen
   googletest
   lcov
   make
   qt
   sphinx


Install the tools
=================

OS X
----

.. code:: bash

   pip3 install -r requirements-dev.txt
   brew install cmake doxygen lcov qt

Linux
-----

.. code:: bash

   pip3 install -r requirements-dev.txt
   apt-get install cmake doxygen lcov qt

Windows
-----

You will need a Windows 10 system, along with the additional software components:

- Cmake, version 3.15.4 or above: https://cmake.org/download
- Conan software: https://conan.io/downloads.html
- Git Client, command line version with shell: https://git-scm.com/download/win
- WinRAR for uncompressing the Swig software: https://www.win-rar.com
- Swig software for windows, zip file: http://www.swig.org/download.html
- Developer Studio at least version 2019, with the following features:
  - Python 2 and Python 3
  - Windows SDK

The recommended overall disk size for the Windows system is 70GB.


Building and running
====================

Below are the steps to build the Mercury library on different OS platforms.

On Linux
--------

.. code:: bash

   make

`CMake <https://cmake.org/documentation/>`_ (3.10.0 minimum to allow us to use some of the newer goodies) is used to build both the project and the tests.

If your linux system is based on Debian Stretch, you can use the `backports <https://backports.debian.org/Instructions/>`_ repositories to pull the latest CMake version. Alternatively, you can point your APT sources to Debian Buster.

On prior Buster Debian distros, you can run this code snippet as root to pull a comfortable CMake version:

.. code:: bash

   printf "deb http://deb.debian.org/debian stretch-backports main" > /etc/apt/sources.list.d/backports.list
   curl -L http://ftp.debian.org/debian/dists/stretch-backports/Release.gpg | apt-key add -
   apt-get update
   apt-get install --allow-unauthenticated -y -t stretch-backports cmake

On Linux
--------
Open a Git Client Shell, clone this repository and then execute the batch file `windows-build.bat`.
Once the batch file terminates, you should see the file `ALL_BUILD.vcxproj` amongst other ones.

You can either open this file inside Developer Studio, and follow the build targets interactively,
or build it from the command line using `msdev`, by opening a PowerShell Developer Studio Command Prompt:

.. code:: bash

   cd build/release
   msdev.exe ALL_BUILD.vcxproj

Which would build all of the available targets. You can be more precise in building specific targets which are available under the `src` subdirectory, for example:

.. code:: bash

   cd build/release
   msdev.exe src/mercury_static.vcxproj

Test
-----

.. code:: bash

   make test

Tests are written with `Google Test <https://github.com/google/googletest>`_. Conan will handle installing all the dependencies here. Coverage reports are generated with ``lcov`` and a report can be found in ``coverage/index.html`` after running the tests.

   make test-library will only cover the core library tests, explained above
   make test-python to run the Python3 tests only. Note that these tests can also run on the target installation system. You need to have ``make`` and ``python-pytest`` tools installed.


Lint
----

.. code:: bash

   make lint

C++ linting is performed by the `CppLint <https://github.com/cpplint/cpplint>`_ tool. The configuration is in the ``CPPLINT.cfg`` file.

Automatic checking of the linting is performed by `CodeFactor <https://www.codefactor.io>`_ for your convenience.


Documentation
-------------

.. code:: bash

   make docs

The base documentation files can be found in the ``docs/source`` directory.

C++ code is marked up with `Doxygen <http://www.doxygen.nl/manual/commands.html>`_ which integrates with `Sphinx <http://www.sphinx-doc.org/en/stable/>`_ using `Breathe <https://breathe.readthedocs.io/en/latest/directives.html>`_.
