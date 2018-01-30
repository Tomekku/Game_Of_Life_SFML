#include "../include/File.hpp"

File::File(std::string filename)
: _filename(filename)
{

}

File::~File()
{

}

std::string File::importFromFile()
{
  std::string content = "";
  std::fstream inputFile(_filename, std::ios_base::in);

  if(inputFile)
  {
    std::string line;
    while( !inputFile.eof() )
    {
      getline(inputFile, line);
      content+=line+'\n';
    }
    inputFile.close();
  }
  else
    throw FILE_NOT_EXIST;
  return content;
}

void File::exportToFile(std::string content)
{
	std::fstream outputFile(_filename, std::ios_base::out);
  if(outputFile)
  {
    outputFile << content;
    outputFile.close();
  }
  else
    throw FILE_SAVE_FAIL;
}

std::istream & operator>>(std::istream &is, File &file)
{
  is >> file;
  return is;
}

std::ostream & operator<<(std::ostream &os, File &file)
{
  os << file;
  return os;
}
