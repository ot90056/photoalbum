#include <iostream>
#include <string>
#include <fstream>
#include <json/json.h>
#include "pabackend.cpp"
#include "vwrap.h"
#include "image_node.h"

using namespace std;

class API
{
public:
    API(){};
    ~API(){};
    void getJson()
    {
        ifstream file("data.json");
        if (!file)
        {
            cout << "File not found" << endl;
            // Create a new file
            ofstream newFile("data.json");
            newFile << "{}";
            newFile.close();
            file.open("data.json");
        }
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(file, root);
        if (!parsingSuccessful)
        {
            cout << "Failed to parse JSON" << endl;
            return;
        }
    };
    LL parseJson()
    {
        LL list;
        ifstream file("data.json");
        bool parsingSuccessful = reader.parse(file, root);
        if (!parsingSuccessful)
        {
            cout << "Failed to parse JSON" << endl;
            return list;
        }
        for (int i = 0; i < root.size(); i++)
        {
            image_node node = createImageNode(root[i]["location"].asString(),root[i]["name"].asString(), root[i]["tags"].asInt());
            list.push(node);
        }
        return list;
    };

    void appendJson(LL list)
    {
        ifstream file("data.json");
        if (!file)
        {
            cout << "File not found" << endl;
            ofstream newFile("data.json");
            newFile << "{}";
            newFile.close();
            file.open("data.json");
        }
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(file, root);
        if (!parsingSuccessful)
        {
            cout << "Failed to parse JSON" << endl;
            return;
        }
        for (int i = 0; i < list.length; i++)
        {
            Json::Value node;
            node["location"] = list.select(i)->location;
            node["name"] = list.select(i)->name;
            node["tags"] = list.select(i)->num_tags;
            root.append(node);
        }
        ofstream newFile("data.json");
        newFile << root;
        newFile.close();

    };

    void writeJson(LL list)
    {
        ofstream file("data.json");
        Json::Value root;
        Json::StyledWriter writer;
        for (int i = 0; i < list.get_Length(); i++)
        {
            Json::Value image;
            image["name"] = list.select(i)->name;
            image["path"] = list.select(i)->location;
            image["tags"] = list.select(i)->tags;
            root.append(image);
        }
        file << writer.write(root);
    }

    struct image_node createImageNode(string location, string name, int num_tags, char **tags = NULL, image_node *next = NULL)
    {
        struct image_node n;
        // Convert from string to char*
        n.location = location;
        n.name = name;
        n.num_tags = num_tags;
        n.next = next;
        return n;
    };

private:
    Json::Value root;
    Json::Reader reader;
    Json::StyledWriter writer;
    string json;
};

int main(int argc, char *argv[])
{
    API api = API();
    LL list = LL();
    list.push(api.createImageNode("C:/Users/Owner/Desktop/1.jpg", "1", 0));
    list.push(api.createImageNode("C:/Users/Owner/Desktop/2.jpg", "2", 0));
    list.push(api.createImageNode("C:/Users/Owner/Desktop/3.jpg", "3", 0));
    api.appendJson(list);
    LL newList = LL();
    newList.push(api.createImageNode("C:/Users/Owner/Desktop/4.jpg", "4", 0));
    newList.push(api.createImageNode("C:/Users/Owner/Desktop/5.jpg", "5", 0));
    newList.push(api.createImageNode("C:/Users/Owner/Desktop/6.jpg", "6", 0));
    api.appendJson(newList);
    newList = api.parseJson();
    newList.print_out();
    return 0;
}
