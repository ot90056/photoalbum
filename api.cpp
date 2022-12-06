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
    API(string name)
    {
        createAlbum(name);
    };
    ~API(){};
    void getJson()
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "File not found" << endl;
            // Create a new file
            ofstream newFile(filename);
            newFile << "{}";
            newFile.close();
            file.open(filename);
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
        ifstream file(filename);
        bool parsingSuccessful = reader.parse(file, root);
        if (!parsingSuccessful)
        {
            cout << "Failed to parse JSON" << endl;
            return list;
        }
        for (int i = 0; i < root.size(); i++)
        {
            image_node node = createImageNode(root[i]["location"].asString(), root[i]["name"].asString(), root[i]["tags"].asInt());
            list.push(node);
        }
        return list;
    };

    void appendJson(LL list)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "File not found" << endl;
            ofstream newFile(filename);
            newFile << "{}";
            newFile.close();
            file.open(filename);
        }
        bool parsingSuccessful = reader.parse(file, root);
        if (!parsingSuccessful)
        {
            cout << "Failed to parse JSON" << endl;
            return;
        }
        root = Json::Value(Json::arrayValue);
        for (int i = 0; i < list.length; i++)
        {
            Json::Value node;
            node["location"] = list.select(i)->location;
            node["name"] = list.select(i)->name;
            node["tags"] = list.select(i)->num_tags;
            root.append(node);
        }
        ofstream newFile(filename);
        newFile << root;
        newFile.close();
    };

    void writeJson(LL list)
    {
        ofstream file(filename);
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
        n.location = location;
        n.name = name;
        n.num_tags = num_tags;
        n.next = next;
        return n;
    };

    void createAlbum(string name)
    {
        filename = "static/albums/" + name + ".json";
    }

private:
    Json::Value root;
    Json::Reader reader;
    Json::StyledWriter writer;
    string filename;
};

int main(int argc, char *argv[])
{
    // Read the arguments
    if (argc > 2)
    {
        string name = argv[1];
        string path = argv[2];
        API api(name);
        api.getJson();
        LL list = api.parseJson();
        list.push(api.createImageNode(path, "test", 0));
        api.appendJson(list);
    }
    else
    {
        cout << "Usage: ./api <album name> <image path>" << endl;
    }
    // LL list = LL();
    // list.push(api.createImageNode("C:/Users/Owner/Desktop/1.jpg", "1", 0));
    // list.push(api.createImageNode("C:/Users/Owner/Desktop/2.jpg", "2", 0));
    // list.push(api.createImageNode("C:/Users/Owner/Desktop/3.jpg", "3", 0));
    // api.appendJson(list);
    // LL newList = LL();
    // newList.push(api.createImageNode("C:/Users/Owner/Desktop/4.jpg", "4", 0));
    // newList.push(api.createImageNode("C:/Users/Owner/Desktop/5.jpg", "5", 0));
    // newList.push(api.createImageNode("C:/Users/Owner/Desktop/6.jpg", "6", 0));
    // api.appendJson(newList);
    // newList = api.parseJson();
    // newList.print_out();
    return 0;
}
