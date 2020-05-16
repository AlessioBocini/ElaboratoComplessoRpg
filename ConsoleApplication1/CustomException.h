#ifndef Error_Manager
	#define Error_Manager
#include <exception>
#include <string>
class TextureException : public std::exception
{
private:
    std::string message = " ";

public:
    TextureException()
    {
        message = "Error in something about Textures";
    }
    TextureException(std::string msg) {
        message = msg;
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class SoundBufferException : public std::exception
{
private:
    std::string message = " ";

public:
    SoundBufferException()
    {
        message = "Error in something about SoundBuffer";
    }
    SoundBufferException(std::string msg) {
        message = msg;
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class FontException : public std::exception {
private:
    std::string message = " ";
public:
    FontException(std::string msg) {
        message = msg;
    }
    FontException() {
        message = "Something went wrong with Font";
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};



#endif // !1

