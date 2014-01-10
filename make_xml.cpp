#include "make_xml.h"

db2xml::XmlMaker::XmlMaker(const RecordList& recordList) : m_recordList(recordList)
{
}

db2xml::XmlMaker::~XmlMaker()
{
}

int db2xml::XmlMaker::get_xml(std::string& strXml)
{
    if (0 != make_nodelist(m_recordList))
    {
        return -1;
    }

    int nSize = m_nodeList.size();
    for (int i = 0; i < nSize; i++)
    {
        std::cout << m_nodeList[i].strName;
        std::cout << " : ";
        std::cout << m_nodeList[i].strXml;
        std::cout << std::endl;
    }

    return 0;
}

int db2xml::XmlMaker::get_error(std::string& strErr)
{
    strErr = m_strError;
    return 0;
}

int db2xml::XmlMaker::make_nodelist(const RecordList& recordList)
{
    RecordItr itr;

    for (itr = recordList.begin(); itr != recordList.end(); itr++)
    {
        if (0 != record2nodes(*itr))
        {
            return -1;
        }
    }

    return 0;
}



int db2xml::XmlMaker::split_string(const std::string& str_src, const char split_ch, StringList& str_dst)
{
    int nLen = str_src.length();
    if (0 == nLen)
    {
        m_strError = "length of strPath is 0";
        return -1;
    }

    std::string str_tmp = "";
    for (int i = 0; i < nLen; i++)
    {
        if (str_src[i] == split_ch)
        {
            str_dst.push_back(str_tmp);
            str_tmp = "";
            continue;
        }

        str_tmp += str_src[i];
    }
    str_dst.push_back(str_tmp);

    return 0;
}


int db2xml::XmlMaker::record2nodes(const Record& record)
{
    StringList nodeNameList;
    if (0 != split_string(record.strPath, '/', nodeNameList))
    {
        return -1;
    }

    int nSize = nodeNameList.size();
    int nParent = -1;
    int iRet = 0;
    for (int i = 0; i < nSize; i++)
    {
        if (0 == i)
        {
            iRet = subPath2Root(nodeNameList[i], nParent);
            if (0 != iRet)
            {
                return -1;
            }
        }
        else if (nSize - 1 == i)
        {
            iRet = subPath2Leaf(nodeNameList[i], record.strValue, nParent);
            if (0 != iRet)
            {
                return -1;
            }
        }
        else
        {
            iRet = subPath2Node(nodeNameList[i], nParent);
            if (0 != iRet)
            {
                return -1;
            }
        }
    }

    return 0;
}

int db2xml::XmlMaker::subPath2Root(const std::string& strSubPath, int& nParent)
{
    if (0 == m_nodeList.size())
    {
        Node tmpNode;
        tmpNode.strName = strSubPath;
        m_nodeList.push_back(tmpNode);
    }
    else if (strSubPath != m_nodeList[0].strName)
    {
        m_strError = "the count of root is not only one: ";
        m_strError += m_nodeList[0].strName;
        m_strError += " and ";
        m_strError += strSubPath;
        return -1;
    }

    nParent = 0;

    return 0;
}

int db2xml::XmlMaker::subPath2Node(const std::string& strSubPath, int& nParent)
{
    if (m_nodeList[nParent].subNode.find(strSubPath) != m_nodeList[nParent].subNode.end())
    {
        nParent = m_nodeList[nParent].subNode[strSubPath];
    }
    else
    {
        Node tmpNode;
        tmpNode.strName = strSubPath;
        m_nodeList.push_back(tmpNode);

        m_nodeList[nParent].subNode.insert(std::pair<const std::string, int>(strSubPath, m_nodeList.size() - 1));

        nParent = m_nodeList.size() - 1;
    }

    return 0;
}

int db2xml::XmlMaker::subPath2Leaf(const std::string& strSubPath, const std::string& strValue, int& nParent)
{
    if (m_nodeList[nParent].subNode.find(strSubPath) != m_nodeList[nParent].subNode.end())
    {
        m_strError = "one node has two same leaf: ";
        m_strError += m_nodeList[nParent].strName;
        m_strError += " ---> ";
        m_strError += strSubPath;
        return -1;
    }

    Node tmpNode;
    tmpNode.strName = strSubPath;
    tmpNode.strXml = "<";
    tmpNode.strXml += strSubPath;
    tmpNode.strXml += ">";
    tmpNode.strXml += strValue;
    tmpNode.strXml += "</";
    tmpNode.strXml += strSubPath;
    tmpNode.strXml += ">";
    tmpNode.bIsOk = true;

    m_nodeList.push_back(tmpNode);

    m_nodeList[nParent].subNode.insert(std::pair<const std::string, int>(strSubPath, m_nodeList.size() - 1));
    
    return 0;
}
