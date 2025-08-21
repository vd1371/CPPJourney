# Quick Reference: Development Tools and Quality Assurance

## Static Analysis Tools

### clang-tidy
```bash
# Basic usage
clang-tidy --checks=* src/*.cpp

# HFT-focused checks
clang-tidy --checks=performance-*,bugprone-*,modernize-* src/*.cpp

# With compilation database
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
clang-tidy -p . src/*.cpp
```

**Key Checks for HFT:**
- `performance-avoid-copy-const-ref-parameters`
- `performance-move-const-arg`
- `modernize-use-nodiscard`

### cppcheck
```bash
# Full analysis
cppcheck --enable=all src/

# Generate XML report
cppcheck --enable=all --xml --xml-version=2 src/ 2> report.xml
```

## Code Formatting

### clang-format
```bash
# Format file
clang-format -i src/file.cpp

# Check formatting
clang-format --dry-run --Werror src/*.cpp

# Format directory
find src/ -name "*.cpp" -exec clang-format -i {} \;
```

**Key Configuration Options:**
- `ColumnLimit: 100` - Better readability on wide screens
- `AlignConsecutiveAssignments: true` - Consistent alignment
- `AllowShortFunctionsOnASingleLine: false` - Clear function separation

## Debugging Tools

### GDB Commands
```bash
# Set breakpoint
(gdb) break function_name

# Conditional breakpoint
(gdb) break function_name if condition

# Watch memory
(gdb) watch -l *ptr

# Examine memory
(gdb) x/16x &variable

# Reverse debugging
(gdb) reverse-step
(gdb) reverse-continue
```

### LLDB Commands
```bash
# Set breakpoint
(lldb) breakpoint set --name function_name

# Run program
(lldb) run

# Set breakpoint with commands
(lldb) breakpoint command add 1
> print variable
> continue
> DONE
```

### Valgrind
```bash
# Memory leak detection
valgrind --tool=memcheck --leak-check=full ./program

# Performance profiling
valgrind --tool=callgrind --dump-instr=yes ./program

# Thread error detection
valgrind --tool=helgrind ./program
```

## CMake Integration

### Enable clang-tidy
```cmake
option(ENABLE_CLANG_TIDY "Enable clang-tidy" ON)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY 
            ${CLANG_TIDY_EXE};
            -checks=*;
            -header-filter=.*
        )
    endif()
endif()
```

### Custom Targets
```cmake
# Formatting target
add_custom_target(format
    COMMAND find ${CMAKE_SOURCE_DIR}/src -name "*.cpp" -exec clang-format -i {} \;
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Analysis target
add_custom_target(analyze
    COMMAND cppcheck --enable=all --xml src/ 2> cppcheck-report.xml
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
```

## CI/CD Integration

### GitHub Actions
```yaml
name: Code Quality
on: [push, pull_request]

jobs:
  quality:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - uses: actions/setup-cpp@v1
        with:
          compiler: gcc
          version: 12
      - run: sudo apt-get install -y clang-tidy cppcheck valgrind
      - run: clang-format --dry-run --Werror src/*.cpp
      - run: clang-tidy --checks=* src/*.cpp
      - run: cppcheck --enable=all src/
```

## Pre-commit Hooks

### .pre-commit-config.yaml
```yaml
repos:
  - repo: https://github.com/pre-commit/mirrors-clang-format
    rev: v16.0.6
    hooks:
      - id: clang-format
        args: [--style=file]
        types: [c++, c]
```

## HFT Best Practices

### Quality Standards
- **Critical paths**: Zero tolerance for memory errors
- **Performance code**: Enforce performance-related checks
- **Style consistency**: Maintain consistent formatting
- **Documentation**: Require docs for complex trading logic

### Performance Considerations
- Use debug builds for comprehensive checking
- Focus analysis on critical path functions
- Balance quality with performance requirements
- Regular profiling of optimized builds

### Team Workflow
1. Automated checks before code review
2. Include tool output in review comments
3. Quality gates for merge requirements
4. Track quality metrics over time
