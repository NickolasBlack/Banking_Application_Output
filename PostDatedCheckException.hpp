#include <stdexcept>

/*
    Post Dated Check Exception
    gets thrown when a check is post dated
*/
class PostDatedCheckException: public std::runtime_error{
    public:
        // Post dated check exception constructor
        PostDatedCheckException(): std::runtime_error(
            "Check is Post Dated"
        ){}
};