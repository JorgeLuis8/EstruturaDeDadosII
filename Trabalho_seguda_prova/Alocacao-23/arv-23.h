#ifndef SRC_H
#define SRC_H

#define FREE 1
#define OCCUPIED 0

typedef struct NodeData
{
    int start;
    int end;
    int status;
} NodeData;

typedef struct Memory
{
    NodeData *info1;
    NodeData *info2;

    struct Memory *left;
    struct Memory *center;
    struct Memory *right;

    int numKeys;

} Memory;

typedef struct Split
{
    Memory *largestNode;
    NodeData *promote;
} Split;

NodeData *CreateInfo(int start, int end, int status);
Memory *createNode(NodeData *information, Memory *leftChild, Memory *centerChild);
int isLeaf(Memory *node);
void AddInfo(Memory **node, NodeData *info, Memory *child);
Split SplitNode(Memory **root, NodeData *info, Memory *child);
void Insert23(Memory **root, Memory *parent, NodeData **promote, int start, int end, int status, int *flag);
Memory *FindSpace(Memory *root, int requiredSpace);
Memory *SourceSpace(Memory *root, int RequiredSpace);
void DisplayInfos(Memory *root);

#endif