#include "make_xml.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    db2xml::RecordList tmpRecordList;
    db2xml::Record record;

    record.strPath = "a/b/c";
    record.strValue = "1";
    tmpRecordList.push_back(record);

    record.strPath = "a/b/d";
    record.strValue = "2";
    tmpRecordList.push_back(record);

    record.strPath = "a/e";
    record.strValue = "3";
    tmpRecordList.push_back(record);

    db2xml::XmlMaker xmlMaker(tmpRecordList);

    std::string tmpStr;
    if (0 != xmlMaker.get_xml(tmpStr))
    {
        xmlMaker.get_error(tmpStr);
        std::cout << tmpStr << std::endl;
    }

    return 0;
}
