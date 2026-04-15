# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/workspace/_deps/quill-src"
  "/workspace/_deps/quill-build"
  "/workspace/_deps/quill-subbuild/quill-populate-prefix"
  "/workspace/_deps/quill-subbuild/quill-populate-prefix/tmp"
  "/workspace/_deps/quill-subbuild/quill-populate-prefix/src/quill-populate-stamp"
  "/workspace/_deps/quill-subbuild/quill-populate-prefix/src"
  "/workspace/_deps/quill-subbuild/quill-populate-prefix/src/quill-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/workspace/_deps/quill-subbuild/quill-populate-prefix/src/quill-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/workspace/_deps/quill-subbuild/quill-populate-prefix/src/quill-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
