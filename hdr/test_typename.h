#include <string>

class Parents
{
    public:
        Parents(){}
        Parents(std::string arg);
        ~Parents(){}
        bool operator<(const Parents* arg) const;
        std::string getMyStr() const;

    protected:
        std::string myStr;
}; 

template <typename T>
class Test0 : public Parents
{
    public:
        Test0(){}
        Test0(std::string arg);
        ~Test0(){}

        T getMynum() const;
        std::string getMyStr() const;
        void setMyStr(std::string arg);
        
        bool operator<(const Test0<T>* arg) const;
        void setMynum(T mynum);

    private:
        T mynum;
};
