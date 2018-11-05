#ifndef SCENEGRAPHNODE_H
#define SCENEGRAPHNODE_H

#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>

using namespace std;

class SceneGraphNode
{
    string name;//name of the node
    int id; //id of the node
    int childCount;//nb of child, useful to agive id to a new child
    SceneGraphNode* aParent;//reference to the parent
    vector<SceneGraphNode> childs;//list of object depending of this object

public :
    SceneGraphNode();
    SceneGraphNode(string n, int i);
    ~SceneGraphNode();
    void ComputeParentPosition();//apply parent position and rotation
    void AddChild(SceneGraphNode c);//add the child to the vector, set its id to count, increase count, set its parent to this, compute its transformations using these transformations
    void SetParent(SceneGraphNode p);
    SceneGraphNode* GetParent();
    int NbOfChilds();
    void SetId(int a);
    int GetID();
    string GetName();
    void SetName(string s);
    vector<SceneGraphNode> GetChilds();
    void ChangeChilds(vector<SceneGraphNode> v);
    SceneGraphNode GetChildAtIndex(int i);
    void SetChild(SceneGraphNode s,int i);
};

#endif // SCENEGRAPHNODE_H
