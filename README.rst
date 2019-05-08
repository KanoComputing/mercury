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


Building and running
====================

Build
-----

.. code:: bash

   make

`CMake <https://cmake.org/documentation/>`_ (3.10.0 minimum to allow us to use some of the newer goodies) is used to build both the project and the tests.

If your linux system is based on Debian Stretch, you can use the `backports <https://backports.debian.org/Instructions/>`_ repositories to pull the latest CMake version. Alternatively, you can point your APT sources to Debian Buster.


Test
-----

.. code:: bash

   make test

Tests are written with `Google Test <https://github.com/google/googletest>`_. Conan will handle installing all the dependencies here. Coverage reports are generated with ``lcov`` and a report can be found in ``coverage/index.html`` after running the tests.


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
