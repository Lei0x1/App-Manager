# 📏 Coding Guidelines

To maintain a consistent and high-quality codebase for the App Manager project, please adhere to the following coding standards and best practices:

## 1. General Guidelines
 - **Clarity**: Write code that is easy to read and understand. Use meaningful variable and function names.
 - **Comments**: Add comments to explain complex logic or decisions. Use block comments to describe functions and their parameters.
 - **Consistent Style**: Follow a consistent style for indentation, spacing, and naming conventions. Use a style guide (e.g., Google C++ Style Guide) as a reference.

## 2. Language-Specific Guidelines
 - **C++**:
   - Use camelCase for variables and functions (e.g., `myVariable`, `calculateSum`).
   - Use PascalCase for class names (e.g., `MyClass`).
   - Enclose header files with include guards to prevent multiple inclusions.

## 3. Code Structure
 - **File Organization**: Organize files logically by functionality (e.g., separate directories for UI, logic, and data management).
 - **Module Design**: Keep functions and classes small and focused on a single responsibility.
 - **Error Handling**: Implement proper error handling for all functions, using exceptions where appropriate.

## 4. Version Control
 - **Commit Messages**: Use clear and descriptive commit messages. Follow the format: `[type]: [subject]` (e.g., `fix: resolve crash on startup`).
 - **Branching**: Use `features` branch for new developments and bug fixes. Merge back into the main branch via pull requests.