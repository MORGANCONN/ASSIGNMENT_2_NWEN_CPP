#include <iostream>
#include "editor2.hh"
#include <cstring>

using namespace editor2;

int main() {
    char buffer[] = "Alice\topened the\n\ndoor\t and   found that it\n\n led into\n";

    std::cout << "Buffer contents: " << buffer << std::endl;
    int r = EditorUtilities::countWords(buffer, sizeof(buffer));
    std::cout << "Output of EditorUtilities::countWords(): " << r << std::endl;
    std::cout << "Actual number of words in buffer       : 10" << std::endl;
}

int EditorUtilities::countWords(char *editing_buffer, int buffer_size) {
    int number_of_words = 0;
    bool in_word = false;
    for (char *i = editing_buffer + sizeof(char); i < editing_buffer + buffer_size; i = i + sizeof(char)) {
        if (!(*i == ' ' || *i == '\t' || *i == '\n' || *i == '\v' || *i == '\f' || *i == '\r')) {
            if ((*(i - sizeof(char)) == ' ' || *(i - sizeof(char)) == '\t' || *(i - sizeof(char)) == '\n' ||
                 *(i - sizeof(char)) == '\v' || *(i - sizeof(char)) == '\f' || *(i - sizeof(char)) == '\r')) {
                number_of_words++;
                in_word = true;
            } else if ((*(i + sizeof(char)) == ' ' || *(i + sizeof(char)) == '\t' || *(i + sizeof(char)) == '\n' ||
                        *(i + sizeof(char)) == '\v' || *(i + sizeof(char)) == '\f' || *(i + sizeof(char)) == '\r') &&
                       !in_word) {
                number_of_words++;
            }
        } else if ((*i == ' ' || *i == '\t' || *i == '\n' || *i == '\v' || *i == '\f' || *i == '\r') && in_word) {
            in_word = false;
        }
    }
    return number_of_words;
}

int EditorUtilities::searchMultipleNoCase(char *editing_buffer, int buffer_size, std::string target, int *positions,
                                          int positionLength) {
    int number_of_occurances = 0;
    char buffer_lowercase[buffer_size / sizeof(char)];
    char *blptr;
    int *posptr = positions;
    int buffer_lowercase_length_orignal = strlen(editing_buffer);
    blptr = buffer_lowercase;
    for (int i = 0; i < (int)(buffer_size / sizeof(char)); i = i + sizeof(char)) {
        buffer_lowercase[i] = (char) tolower(editing_buffer[i]);
    }
    char char_target[target.size() + 1];
    strcpy(char_target, target.c_str());
    while (strstr(buffer_lowercase, char_target) != nullptr) {
        number_of_occurances++;
        char *Location_address = strstr(buffer_lowercase, char_target);
        int array_location = static_cast<int>(Location_address - blptr);
        int target_length = strlen(char_target);
        int end_of_target_index = array_location + target_length + 1;
        int buffer_lowercase_length = strlen(buffer_lowercase);
        *posptr = (buffer_lowercase_length_orignal - buffer_lowercase_length) + array_location;
        posptr = posptr + 1;
        for (int i = end_of_target_index; i < (int)(buffer_size / sizeof(char)); i++) {
            buffer_lowercase[i - end_of_target_index] = buffer_lowercase[i];
        }
        buffer_lowercase[buffer_lowercase_length - end_of_target_index]='\0';
    }
    return number_of_occurances;
}
