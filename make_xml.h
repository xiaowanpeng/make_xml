#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace db2xml
{
    const std::string STR_XML_HEAD = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>";

    struct Record
    {
        std::string strPath; // A/B/C
        std::string strValue;
    };

    typedef std::map<std::string, int> Name2Node;
    typedef std::map<std::string, int>::iterator Name2NodeItr;

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
        Name2Node subNode;
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
        int split_string(const std::string& str_src, const char split_ch, StringList& str_dst);

        int make_nodelist(const RecordList& recordList);

        int record2nodes(const Record& record);

        int subPath2Root(const std::string& strSubPath, int& nParent);
        int subPath2Node(const std::string& strSubPath, int& nParent);
        int subPath2Leaf(const std::string& strSubPath, const std::string& strValue, int& nParent);

        int get_subXml(const int nParent, std::string& strSubXml);

    private:
        NodeList m_nodeList;
        RecordList m_recordList;
        std::string m_strError;
    };
};
