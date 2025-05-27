
#include "node.h"

class LlistaDoble
{
    public:
        LlistaDoble();
        ~LlistaDoble();

        bool empty() const;
        Node* begin() const;
        Node* rbegin() const;
        Node* insert(const int &valor, Node* posicio);
        Node* erase(Node* posicio);
        void unique();
        LlistaDoble& operator=(const LlistaDoble& llista);
    private:
        Node* m_primer;
        Node* m_ultim;
};