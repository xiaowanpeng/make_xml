#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

namespace db2xml
{
    struct Record
    {
        std::string strPath; // A/B/C
        std::string strValue;
    };

    typedef std::map<std::string, int> Name2pNode;
    typedef std::map<std::string, int>::iterator Name2pNodeItr;

    struct Node
    {
        Node() : 
            strName(""),
            strXml(""),
            bIsOk(false)
        {
        };

        std::string strName;
        std::string strXml;
        Name2pNode subNode;
        bool bIsOk;
    };


    typedef std::vector<Node> NodeList;
    typedef std::vector<Record> RecordList;
    typedef std::vector<std::string> StringList;

    typedef std::vector<Record>::const_iterator RecordItr;

    class XmlMaker
    {
    public:
        XmlMaker(const RecordList& recordList);
        ~XmlMaker();

        int get_xml(std::string& strXml);
        int get_error(std::string& strErr);

    private:
        int make_nodelist(const RecordList& recordList);
        int split_string(const std::string& str_src, const char split_ch, StringList& str_dst);
        int record2nodes(const Record& record);
        int subPath2Root(const std::string& strSubPath, int& nParent);
        int subPath2Node(const std::string& strSubPath, int& nParent);
        int subPath2Leaf(const std::string& strSubPath, const std::string& strValue, int& nParent);

    private:
        NodeList m_nodeList;
        RecordList m_recordList;
        std::string m_strError;
    };
};
