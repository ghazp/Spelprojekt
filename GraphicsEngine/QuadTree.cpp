#include "QuadTree.h"

QuadTree::QuadTree()
{
	this->m_parent = NULL;
}

QuadTree::QuadTree(int _levels, D3DXVECTOR2 _min, D3DXVECTOR2 _max)
{
	this->m_parent = new QuadTreeNode(_levels, _min, _max);
}

QuadTree::~QuadTree()
{
	if(this->m_parent)
		delete this->m_parent;
}

void QuadTree::addModel(Model* _model)
{
	this->m_parent->addModel(_model);
}

stack<Model*> QuadTree::getModels()const
{
	stack<Model*> models;

	this->m_parent->getModels(models);

	return models;
}