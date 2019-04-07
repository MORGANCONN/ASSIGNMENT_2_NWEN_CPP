//
// Created by Connor on 3/04/2019.
//

#ifndef ASSIGNMENT_2_CPP_NWEN241_EDITOR2_H
#define ASSIGNMENT_2_CPP_NWEN241_EDITOR2_H
#include <string>
namespace editor2{
    class EditorUtilities{
    public:
        static int countWords(char *editing_buffer, int buffer_size);
        static int searchMultipleNoCase(char *editing_buffer,  int buffer_size, std::string target, int positions[], int positionLength);
    };
}
#endif //ASSIGNMENT_2_CPP_NWEN241_EDITOR2_H
