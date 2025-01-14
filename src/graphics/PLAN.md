#pragma once

// block-quad
const vec3(0,0,0)
const vec3(0,1,0)
const vec3(1,0,0)
const vec3(1,1,0)

class Block{
    enum Faces{
        UP, DOWN, LEFT,RIGHT, FRONT,BACK,
    };
    int id;
}
class ChunkManager(){
    load(worldPos){
        loadedChunks[worldPos] = Chunk(&loadedChunks)
    }
private:
    std::unordered_map<Position, Chunk> loadedChunks;
}

class Chunk{
    Chunk(){
    for i
    for j
    for k
        mesh.addBlock(k){
            if air
                return;

            if UP is air
                mesh.addFace(face)
            if DOWN is air
                mesh.addFace(face)
            ...
        }
    }
private:
    ChunkMesh mesh;
}

class ChunkMesh{
    #define UP_VERTEX ...
    #define DOWN_VERTEX ...

    addBlock();
    addFace();
    private:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
}
