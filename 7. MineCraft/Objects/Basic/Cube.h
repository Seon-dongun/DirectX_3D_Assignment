#pragma once

class Cube : public GameObject
{
public:
    Cube(Float3 size = { 1, 1, 1 });
    ~Cube();

    //void Update();
    void Render();

private:    
    Mesh<VertexUV>* mesh;
};