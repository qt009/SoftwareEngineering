#[=======================================================================[.rst:
Flags
-----

This module defines functions to help use the Google Test infrastructure.  Two
mechanisms for adding tests are provided. :command:`gtest_add_tests` has been
around for some time, originally via ``find_package(GTest)``.
:command:`gtest_discover_tests` was introduced in CMake 3.10.

The (older) :command:`gtest_add_tests` scans source files to identify tests.
This is usually effective, with some caveats, including in cross-compiling
environments, and makes setting additional properties on tests more convenient.
However, its handling of parameterized tests is less comprehensive, and it
requires re-running CMake to detect changes to the list of tests.

The (newer) :command:`gtest_discover_tests` discovers tests by asking the
compiled test executable to enumerate its tests.  This is more robust and
provides better handling of parameterized tests, and does not require CMake
to be re-run when tests change.  However, it may not work in a cross-compiling
environment, and setting test properties is less convenient.

More details can be found in the documentation of the respective functions.

Both commands are intended to replace use of :command:`add_test` to register
tests, and will create a separate CTest test for each Google Test test case.
Note that this is in some cases less efficient, as common set-up and tear-down
logic cannot be shared by multiple test cases executing in the same instance.
However, it provides more fine-grained pass/fail information to CTest, which is
usually considered as more beneficial.  By default, the CTest test name is the
same as the Google Test name (i.e. ``suite.testcase``); see also
``TEST_PREFIX`` and ``TEST_SUFFIX``.

.. command:: gtest_add_tests

  Automatically add tests with CTest by scanning source code for Google Test
  macros::

    gtest_add_tests(TARGET target
                    [SOURCES src1...]
                    [EXTRA_ARGS arg1...]
                    [WORKING_DIRECTORY dir]
                    [TEST_PREFIX prefix]
                    [TEST_SUFFIX suffix]
                    [SKIP_DEPENDENCY]
                    [TEST_LIST outVar]
    )

  ``gtest_add_tests`` attempts to identify tests by scanning source files.
  Although this is generally effective, it uses only a basic regular expression
  match, which can be defeated by atypical test declarations, and is unable to
  fully "split" parameterized tests.  Additionally, it requires that CMake be
  re-run to discover any newly added, removed or renamed tests (by default,
  this means that CMake is re-run when any test source file is changed, but see
  ``SKIP_DEPENDENCY``).  However, it has the advantage of declaring tests at
  CMake time, which somewhat simplifies setting additional properties on tests,
  and always works in a cross-compiling environment.

  The options are:

  ``TARGET target``
    Specifies the Google Test executable, which must be a known CMake
    executable target.  CMake will substitute the location of the built
    executable when running the test.

  ``SOURCES src1...``
    When provided, only the listed files will be scanned for test cases.  If
    this option is not given, the :prop_tgt:`SOURCES` property of the
    specified ``target`` will be used to obtain the list of sources.

  ``EXTRA_ARGS arg1...``
    Any extra arguments to pass on the command line to each test case.

  ``WORKING_DIRECTORY dir``
    Specifies the directory in which to run the discovered test cases.  If this
    option is not provided, the current binary directory is used.

  ``TEST_PREFIX prefix``
    Specifies a ``prefix`` to be prepended to the name of each discovered test
    case.  This can be useful when the same source files are being used in
    multiple calls to ``gtest_add_test()`` but with different ``EXTRA_ARGS``.

  ``TEST_SUFFIX suffix``
    Similar to ``TEST_PREFIX`` except the ``suffix`` is appended to the name of
    every discovered test case.  Both ``TEST_PREFIX`` and ``TEST_SUFFIX`` may
    be specified.

  ``SKIP_DEPENDENCY``
    Normally, the function creates a dependency which will cause CMake to be
    re-run if any of the sources being scanned are changed.  This is to ensure
    that the list of discovered tests is updated.  If this behavior is not
    desired (as may be the case while actually writing the test cases), this
    option can be used to prevent the dependency from being added.

  ``TEST_LIST outVar``
    The variable named by ``outVar`` will be populated in the calling scope
    with the list of discovered test cases.  This allows the caller to do
    things like manipulate test properties of the discovered tests.

  .. code-block:: cmake

    include(GoogleTest)
    add_executable(FooTest FooUnitTest.cxx)
    gtest_add_tests(TARGET      FooTest
                    TEST_SUFFIX .noArgs
                    TEST_LIST   noArgsTests
    )
    gtest_add_tests(TARGET      FooTest
                    EXTRA_ARGS  --someArg someValue
                    TEST_SUFFIX .withArgs
                    TEST_LIST   withArgsTests
    )
    set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
    set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)

  For backward compatibility, the following form is also supported::

    gtest_add_tests(exe args files...)

  ``exe``
    The path to the test executable or the name of a CMake target.
  ``args``
    A ;-list of extra arguments to be passed to executable.  The entire
    list must be passed as a single argument.  Enclose it in quotes,
    or pass ``""`` for no arguments.
  ``files...``
    A list of source files to search for tests and test fixtures.
    Alternatively, use ``AUTO`` to specify that ``exe`` is the name
    of a CMake executable target whose sources should be scanned.

  .. code-block:: cmake

    include(GoogleTest)
    set(FooTestArgs --foo 1 --bar 2)
    add_executable(FooTest FooUnitTest.cxx)
    gtest_add_tests(FooTest "${FooTestArgs}" AUTO)

.. command:: gtest_discover_tests

  Automatically add tests with CTest by querying the compiled test executable
  for available tests::

    gtest_discover_tests(target
                         [EXTRA_ARGS arg1...]
                         [WORKING_DIRECTORY dir]
                         [TEST_PREFIX prefix]
                         [TEST_SUFFIX suffix]
                         [NO_PRETTY_TYPES] [NO_PRETTY_VALUES]
                         [PROPERTIES name1 value1...]
                         [TEST_LIST var]
                         [DISCOVERY_TIMEOUT seconds]
    )

  ``gtest_discover_tests`` sets up a post-build command on the test executable
  that generates the list of tests by parsing the output from running the test
  with the ``--gtest_list_tests`` argument.  Compared to the source parsing
  approach of :command:`gtest_add_tests`, this ensures that the full list of
  tests, including instantiations of parameterized tests, is obtained.  Since
  test discovery occurs at build time, it is not necessary to re-run CMake when
  the list of tests changes.
  However, it requires that :prop_tgt:`CROSSCOMPILING_EMULATOR` is properly set
  in order to function in a cross-compiling environment.

  Additionally, setting properties on tests is somewhat less convenient, since
  the tests are not available at CMake time.  Additional test properties may be
  assigned to the set of tests as a whole using the ``PROPERTIES`` option.  If
  more fine-grained test control is needed, custom content may be provided
  through an external CTest script using the :prop_dir:`TEST_INCLUDE_FILES`
  directory property.  The set of discovered tests is made accessible to such a
  script via the ``<target>_TESTS`` variable.

  The options are:

  ``target``
    Specifies the Google Test executable, which must be a known CMake
    executable target.  CMake will substitute the location of the built
    executable when running the test.

  ``EXTRA_ARGS arg1...``
    Any extra arguments to pass on the command line to each test case.

  ``WORKING_DIRECTORY dir``
    Specifies the directory in which to run the discovered test cases.  If this
    option is not provided, the current binary directory is used.

  ``TEST_PREFIX prefix``
    Specifies a ``prefix`` to be prepended to the name of each discovered test
    case.  This can be useful when the same test executable is being used in
    multiple calls to ``gtest_discover_tests()`` but with different
    ``EXTRA_ARGS``.

  ``TEST_SUFFIX suffix``
    Similar to ``TEST_PREFIX`` except the ``suffix`` is appended to the name of
    every discovered test case.  Both ``TEST_PREFIX`` and ``TEST_SUFFIX`` may
    be specified.

  ``NO_PRETTY_TYPES``
    By default, the type index of type-parameterized tests is replaced by the
    actual type name in the CTest test name.  If this behavior is undesirable
    (e.g. because the type names are unwieldy), this option will suppress this
    behavior.

  ``NO_PRETTY_VALUES``
    By default, the value index of value-parameterized tests is replaced by the
    actual value in the CTest test name.  If this behavior is undesirable
    (e.g. because the value strings are unwieldy), this option will suppress
    this behavior.

  ``PROPERTIES name1 value1...``
    Specifies additional properties to be set on all tests discovered by this
    invocation of ``gtest_discover_tests``.

  ``TEST_LIST var``
    Make the list of tests available in the variable ``var``, rather than the
    default ``<target>_TESTS``.  This can be useful when the same test
    executable is being used in multiple calls to ``gtest_discover_tests()``.
    Note that this variable is only available in CTest.

  ``DISCOVERY_TIMEOUT num``
    Specifies how long (in seconds) CMake will wait for the test to enumerate
    available tests.  If the test takes longer than this, discovery (and your
    build) will fail.  Most test executables will enumerate their tests very
    quickly, but under some exceptional circumstances, a test may require a
    longer timeout.  The default is 5.  See also the ``TIMEOUT`` option of
    :command:`execute_process`.

    .. note::

      In CMake versions 3.10.1 and 3.10.2, this option was called ``TIMEOUT``.
      This clashed with the ``TIMEOUT`` test property, which is one of the
      common properties that would be set with the ``PROPERTIES`` keyword,
      usually leading to legal but unintended behavior.  The keyword was
      changed to ``DISCOVERY_TIMEOUT`` in CMake 3.10.3 to address this
      problem.  The ambiguous behavior of the ``TIMEOUT`` keyword in 3.10.1
      and 3.10.2 has not been preserved.

#]=======================================================================]

#[[
    Adds the given flag to the specified flagList, if not already existing
    addFlag(target)
#]]
macro(addFlag flagList flag)
    if (NOT ${flagList} MATCHES "(^| )${flag}( |$)")
        # Checks if the flagList is empty
        if (NOT ${flagList} OR (${flagList} MATCHES "^ *$"))
            set(${flagList} ${flag})
        else ()
            set(${flagList} "${${flagList}} ${flag}")
        endif ()
    endif ()
endmacro(addFlag)

# A list of supported Compilers
# Simply add Compilers to the list in uppercase (do not forget to update the documentations; search for COMPILER_TYPE in the file. These should be all appearances in the documentation)
# The entries will be compared via MATCHES to the uppercase version of ${CMAKE_CXX_COMPILER_ID}
set(__SUPPORTED_COMPILER "GNU;CLANG")

#[[
    Adds the passed flags to the specified property
    If a target is specified, the targets property will be changed, otherwise the global property will be changed
    __addFlagsToProperty(property flag1 ...
                         ['COMPILER_TYPE' flag1 ...]
                         [PARENT_SCOPE] | [TARGET target]
    )

    ``'COMPILER_TYPE' flag1 ...``
    Specifies compiler specific flags. The COMPILER_TYPE is one of: GNU, CLANG
    ``PARENT_SCOPE``
    Specifies whether the property of this scope or the parent should be changed (note this is a macro not a function)
    ``TARGET target``
    Specifies the target of which the property should be changed. Can not be used together with PARENT_SCOPE
#]]
macro(__addFlagsToProperty property)
    cmake_parse_arguments("" "PARENT_SCOPE" "TARGET" "${__SUPPORTED_COMPILER}" ${ARGN})
    if (_TARGET AND _PARENT_SCOPE)
        message(FATAL_ERROR "Use either TARGET or PARENT_SCOPE, not both")
    endif ()

    # Get the pervious set flags from the property
    if (_TARGET)
        if (NOT TARGET ${_TARGET})
            message(FATAL_ERROR "TARGET ${_TARGET} could not be found. Perhaps it has not yet been created.")
        endif ()
        get_property(has_flags TARGET ${_TARGET} PROPERTY ${property} SET)
        if (has_flags)
            get_property(flags TARGET ${_TARGET} PROPERTY ${property})
        else ()
            set(flags)
        endif ()
    else ()
        set(flags ${${property}})
    endif ()

    # Add all compiler independet flags
    foreach (flag ${_UNPARSED_ARGUMENTS})
        addFlag(flags "${flag}")
    endforeach ()

    # Add all compiler dependet flags
    string(TOUPPER "${CMAKE_CXX_COMPILER_ID}" _COMPILER_ID)
    foreach (compiler ${__SUPPORTED_COMPILER})
        if (_COMPILER_ID MATCHES "${compiler}")
            foreach (flag ${_${compiler}})
                addFlag(flags "${flag}")
            endforeach ()
        endif ()
    endforeach ()

    # Set the flags to the property
    if (_TARGET)
        set_target_properties(${_TARGET} PROPERTIES ${property} ${flags})
    elseif (_PARENT_SCOPE)
        set(${property} ${flags} PARENT_SCOPE)
    else ()
        set(${property} ${flags})
    endif ()
endmacro(__addFlagsToProperty)

#[[
    Adds the passed flags to the specified property
    If a target is specified, the targets property will be changed, otherwise the global property will be changed
    addFlagsToProperty(property flag1 ...
                       ['COMPILER_TYPE' flag1 ...]
                       [TARGET target]
    )

    ``'COMPILER_TYPE' flag1 ...``
    Specifies compiler specific flags. The COMPILER_TYPE is one of: GNU, CLANG
    ``TARGET target``
    Specifies the target of which the property should be changed
#]]
function(addFlagsToProperty property)
    cmake_parse_arguments("" "" "TARGET" "" ${ARGN})
    # If TARGET is passed, PARENT_SCOPE could not be used
    if (_TARGET)
        __addFlagsToProperty(property ${ARGN})
    else ()
        __addFlagsToProperty(property PARENT_SCOPE ${ARGN})
    endif ()
endfunction()

#[[
    Parse the arguments of the add*Flags() functions, with the given options
    __parseAddXFlags(options arg1 ...)

    Afterwards:
        'targets' holds the passed targets
        'args' holds the aruments passable to __addFlagsToProperty
        Each value of options is a variable holding whether it has been passed as argument or not
#]]
macro(__parseAddXFlags options)
    cmake_parse_arguments("" "${options}" "" "TARGETS;${__SUPPORTED_COMPILER}" ${ARGN})

    # Renaming _TARGETS to targets
    if (_TARGETS)
        set(targets ${_TARGETS})
    endif ()

    # Passing all unparsed arguments at first to args
    if (_UNPARSED_ARGUMENTS)
        list(APPEND args ${_UNPARSED_ARGUMENTS})
    endif ()
    # Passing all compiler arguments to args
    foreach (compiler ${__SUPPORTED_COMPILER})
        if (_${compiler})
            list(APPEND args ${compiler} ${_${compiler}})
        endif ()
    endforeach ()

    # Check if any of the options have been passed and generate a string holding the options to print them in case of an error
    unset(optionsString)
    foreach (option ${options})
        # Renaming _${option} to ${option} (remove underscore infront of the option variable)
        set(${option} ${_${option}})
        if (_${option})
            set(AT_LEAST_ONE_OPTION_PASSED TRUE)
        endif ()
        if (optionsString)
            set(optionsString "${optionsString}, ")
        endif ()
        set(optionsString "${optionsString}${option}")
    endforeach ()

    if (NOT (_TARGETS OR AT_LEAST_ONE_OPTION_PASSED))
        if (NOT args)
            message(FATAL_ERROR "Neither flags, nor TARGETS, ${optionsString} were given")
        else ()
            message(FATAL_ERROR "Neither TARGETS, nor ${optionsString} were given")
        endif ()
    endif ()

    if (NOT args)
        message(FATAL_ERROR "No flags were given")
    endif ()
endmacro(__parseAddXFlags)

#[[
    Adds the given flags to the specified targets compile flags and/or to CMAKE_CXX_FLAGS
    addCompilerFlags(flag1 ...
                     ['COMPILER_TYPE' flag1 ...]
                     [GLOBAL]
                     [TARGETS target1 ...]
    )

    ``'COMPILER_TYPE' flag1 ...``
    Specifies compiler specific flags. The COMPILER_TYPE is one of: GNU, CLANG
    ``GLOBAL``
    If given, the flags were added to CMAKE_CXX_FLAGS
    ``TARGETS target1 ...``
    Specifies the targets to which the flags should be added
#]]
function(addCompilerFlags)
    __parseAddXFlags("GLOBAL" ${ARGN})

    foreach (target ${targets})
        __addFlagsToProperty(COMPILE_FLAGS TARGET ${target} ${args})
    endforeach ()

    if (GLOBAL)
        __addFlagsToProperty(CMAKE_CXX_FLAGS PARENT_SCOPE ${args})
    endif ()
endfunction(addCompilerFlags)

#[[
    Adds the given flags to the specified targets link flags, CMAKE_EXE_LINKER_FLAGS, CMAKE_STATIC_LINKER_FLAGS, CMAKE_SHARED_LINKER_FLAGS, and/or CMAKE_MODULE_LINKER_FLAGS
    addCompilerFlags(flag1 ...
                     ['COMPILER_TYPE' flag1 ...]
                     [EXECUTABLE]
                     [STATIC]
                     [SHARED]
                     [MODULE]
                     [TARGETS target1 ...]
    )

    ``'COMPILER_TYPE' flag1 ...``
    Specifies compiler specific flags. The COMPILER_TYPE is one of: GNU, CLANG
    ``EXECUTABLE``
    If given, the flags were added to CMAKE_EXE_LINKER_FLAGS
    ``STATIC``
    If given, the flags were added to CMAKE_STATIC_LINKER_FLAGS
    ``SHARED``
    If given, the flags were added to CMAKE_SHARED_LINKER_FLAGS
    ``MODULE``
    If given, the flags were added to CMAKE_MODULE_LINKER_FLAGS
    ``TARGETS target1 ...``
    Specifies the targets to which the flags should be added
#]]
function(addLinkerFlags)
    __parseAddXFlags("EXECUTABLE;STATIC;SHARED;MODULE" ${ARGN})

    foreach (target ${targets})
        get_target_property(targetType ${target} TYPE)
        # Checking whether the target is a static library (uses a different property) or not
        if (targetType STREQUAL "STATIC_LIBRARY")
            __addFlagsToProperty(STATIC_LIBRARY_FLAGS TARGET ${target} ${args})
        else ()
            __addFlagsToProperty(LINK_FLAGS TARGET ${target} ${args})
        endif ()
    endforeach ()

    if (EXECUTABLE)
        __addFlagsToProperty(CMAKE_EXE_LINKER_FLAGS PARENT_SCOPE ${args})
    endif ()
    if (STATIC)
        __addFlagsToProperty(CMAKE_STATIC_LINKER_FLAGS PARENT_SCOPE ${args})
    endif ()
    if (SHARED)
        __addFlagsToProperty(CMAKE_SHARED_LINKER_FLAGS PARENT_SCOPE ${args})
    endif ()
    if (MODULE)
        __addFlagsToProperty(CMAKE_MODULE_LINKER_FLAGS PARENT_SCOPE ${args})
    endif ()
endfunction(addLinkerFlags)
