#pragma once

class ModelAnimator : public Model
{
protected:
    struct ClipTransform
    {
        Matrix transform[MAX_FRAME][MAX_BONE];
    };

    struct Frame
    {
        int clip = 0;
        int curFrame = 0;
        float time = 0.0f;
        float scale = 1.0f;
    };

    struct Motion
    {
        float takeTime = 0.2f;
        float tweenTime = 0.0f;
        float runningTime = 0.0f;
        float pading;

        Frame cur, next;

        Motion()
        {
            next.clip = -1.0f;
        }
    };

    class FrameBuffer : public ConstBuffer
    {
    public:
        FrameBuffer() : ConstBuffer(&motion, sizeof(Motion))
        {
        };

        Motion* GetData() { return &motion; }

    private:
        Motion motion;
    };

public:
    ModelAnimator(string name);
    ~ModelAnimator();

    void Update();
    void Render();    

    void ReadClip(string clipName, UINT clipNum = 0);
    void PlayClip(int clip, float scale = 1.0f, float takeTime = 0.2f);

    void CreateTexture();

    Matrix GetTransformByNode(int nodeIndex);

    ModelClip* GetClip(UINT clip) { return clips[clip]; }

protected:    
    void CreateClipTransform(UINT index);
    void UpdateFrame();

protected:
    vector<ModelClip*> clips;

    ClipTransform* clipTransforms;
    ClipTransform* nodeTransforms;

    ID3D11Texture2D* texture = nullptr;
    ID3D11ShaderResourceView* srv;

    FrameBuffer* frameBuffer;

    bool isPlay = true;
};
