#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using ChoiceVector = std::vector<std::pair<std::string, int>>;
inline ChoiceVector DEFAULT_EMPTY_CHOICES{};

class DialogBox;

class DialogManager {
public:
    DialogManager() {}
    DialogManager(DialogBox * box);

    static const int NULL_ID = 0;

    struct Node {
        Node() {}
        Node(const std::string &text, const int id, const int nextId,
                const ChoiceVector &choices = DEFAULT_EMPTY_CHOICES):
            text(text), id(id), nextId(nextId), choices(choices) {}
        Node(const Node& other):
            text(other.text), id(other.id), nextId(other.nextId), choices(other.choices) {}
        Node &operator=(const Node&other) {
            text = other.text;
            id = other.id;
            nextId = other.nextId;
            choices = other.choices;
            return *this;
        }

        std::string text;
        int id;
        int nextId;
        std::vector<std::pair<std::string, int>> choices;
    };

    void addNode(const Node &node) {
        if (node.id == NULL_ID)
            throw std::runtime_error("Node id cannot be NULL");
        nodes[node.id] = node; 
    }

    // Update the dialog manager
    void update();

    // Go to node
    void jumpToNode(const int nodeId);

    // Set box
    void setBox(DialogBox * box);
    
private:
    int currentId = NULL_ID;
    std::map<int, Node> nodes;
    DialogBox * box = nullptr;
    double lastSkipPress = 0.0;
};

#endif