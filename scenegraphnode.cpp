/*#include "scenegraphnode.h"
#include <QVector3D>
#include <QQuaternion>

using namespace std;

SceneGraphNode::SceneGraphNode(){
    name = "scene";
    id = 0;
    childCount = 0;
    aParent = NULL;
    childs = vector<SceneGraphNode>();
}

SceneGraphNode::SceneGraphNode(string n, int i){
        name = n;
        id = i;
        childCount = 0;
        aParent = NULL;
        childs = vector<SceneGraphNode>();
}

SceneGraphNode::~SceneGraphNode(){
    childs.clear();
}

void SceneGraphNode::AddChild(SceneGraphNode c){
    c.id = childCount;
    c.aParent = this;
    c.ComputeParentPosition();
    childCount++;
    childs.push_back(c);
}

void SceneGraphNode::SetParent(SceneGraphNode p){
    aParent = &p;
}

SceneGraphNode* SceneGraphNode::GetParent(){
    return aParent;
}

int SceneGraphNode::NbOfChilds(){
    return childCount;
}

void SceneGraphNode::SetId(int a){
    id = a;
}

int SceneGraphNode::GetID(){
    return id;
}

string SceneGraphNode::GetName(){
    return name;
}

void SceneGraphNode::SetName(string s){
    name = s;
}

vector<SceneGraphNode> SceneGraphNode::GetChilds(){
    return childs;
}

void SceneGraphNode::ChangeChilds(vector<SceneGraphNode> v){
    for (int i = 0; i < v.size(); i++){
        v[i].aParent = this;
    }
}

SceneGraphNode SceneGraphNode::GetChildAtIndex(int i){
    return childs[i];
}

void SceneGraphNode::SetChild(SceneGraphNode s,int i){
    s.aParent = this;
    if (i < childs.size())
        childs[i] = s;
}
*/
