#ifndef DIALOG_MANAGER_H
#define DIALOG_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>
#include "raylib.h"

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
        Node(const int id, const int nextId, const std::string &text): id(id), nextId(nextId), text(text) {}
        Node(const Node& other):
            id(other.id), nextId(other.nextId), choices(other.choices), text(other.text), title(other.title),
            textColor(other.textColor), titleColor(other.titleColor), onActive(other.onActive), forward(other.forward) {}
        Node &operator=(const Node &other) {
            id = other.id;
            nextId = other.nextId;
            choices = other.choices;
            text = other.text;
            title = other.title;
            textColor = other.textColor;
            titleColor = other.titleColor;
            onActive = other.onActive;
            forward = other.forward;
            return *this;
        }

        Node& setId(int id) { this->id = id; return *this; }
        Node& setNextId(int nextId) { this->nextId = nextId; return *this; }
        Node& addChoice(const std::string &choice, const int nextId) {
            choices.push_back(std::make_pair(choice, nextId));
            return *this;
        }
        Node& setText(const std::string &text) { this->text = text; return *this; }
        Node& setTitle(const std::string &title) { this->title = title; return *this; }
        Node& setTextColor(Color textColor) { this->textColor = textColor; return *this; }
        Node& setTitleColor(Color titleColor) { this->titleColor = titleColor; return *this; }
        Node& setOnActive(std::function<void(Node&)> onActive) { this->onActive = onActive; return *this; }
        Node& setBackwards() { this->forward = false; return *this; }

        int id, nextId;
        std::vector<std::pair<std::string, int>> choices = DEFAULT_EMPTY_CHOICES;
        std::string text = "";
        std::string title = "";
        Color textColor = BLACK;
        Color titleColor = ORANGE;
        bool forward = true;
        std::function<void(Node&)> onActive = [](Node&){};
    };

    void addNode(const Node &node) {
        if (node.id == NULL_ID)
            throw std::runtime_error("Node id cannot be NULL");
        nodes[node.id] = node; 
    }

    // Update the dialog manager
    void update();

    // Advance to next node, or complete text
    void advance();

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