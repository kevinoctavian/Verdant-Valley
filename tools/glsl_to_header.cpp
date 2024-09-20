#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Function to read the shader file into a vector of unsigned char
std::vector<unsigned char> readShaderFile(const std::string &filePath) {
  std::ifstream file(filePath, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open shader file: " << filePath << std::endl;
    exit(1);
  }

  std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());
  return buffer;
}

// Function to write the shader data as a C header file
void writeHeaderFile(const std::string &outputPath,
                     const std::vector<unsigned char> &shaderData,
                     const std::string &variableName) {
  std::ofstream outputFile(outputPath);
  if (!outputFile.is_open()) {
    std::cerr << "Failed to open output header file: " << outputPath
              << std::endl;
    exit(1);
  }

  // Write the shader data to the header file
  outputFile << "#pragma once\n";
  outputFile << "const unsigned char " << variableName << "[] = {\n";

  for (size_t i = 0; i < shaderData.size(); ++i) {
    outputFile << "0x" << std::hex << (int)shaderData[i];
    if (i < shaderData.size() - 1)
      outputFile << ", ";
    if ((i + 1) % 12 == 0)
      outputFile << "\n";
  }

  outputFile << "\n};\n\n";

  // Write the length of the shader data as a constant
  outputFile << "const unsigned int " << variableName << "_len = " << std::dec
             << shaderData.size() << ";\n";
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <input_shader_file> <output_header_file> <variable_name>\n";
    return 1;
  }

  std::string inputShaderPath = argv[1];
  std::string outputHeaderPath = argv[2];
  std::string variableName = argv[3];

  // Read the shader file
  std::vector<unsigned char> shaderData = readShaderFile(inputShaderPath);

  // Write the shader data to the header file
  writeHeaderFile(outputHeaderPath, shaderData, variableName);

  return 0;
}
