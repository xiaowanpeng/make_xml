#include <string>
#include <vector>
#include <iostream>

namespace db2xml
{
    struct node
    {
        std::string strName;
        std::string strParent;
        std::string strValue;
        bool        bIsLeaf;
    };

    typedef std::vector<node> NodeList;

    class XmlMaker
    {
    public:
        XmlMaker(const NodeList& nodeList);
        ~XmlMaker();

    private:
        NodeList m_nodeList;
    };
};
