#pragma once

class Transform
{
public:
    Transform();

    void GUIRender();

    void UpdateWorld();

    void Translate(Vector3 direction);
    void Rotate(Vector3 direction);

    void Save();
    void Load();

    bool IsActive();

    Vector3 GetLocalPosition() const { return localPosition; }
    Vector3 GetLocalRotation() const { return localRotation; }
    Vector3 GetLocalScale() const { return localScale; }

    Vector3 GetGlobalPosition() const { return globalPosition; }
    Vector3 GetGlobalRotation() const { return globalRotation; }
    Vector3 GetGlobalScale() const { return globalScale; }

    void SetLocalPosition(const Vector3& position) { localPosition = position; }
    void SetLocalRotation(const Vector3& rotation) { localRotation = rotation; }
    void SetLocalScale(const Vector3& scale) { localScale = scale; }

    Transform* GetParent() { return parent; }
    void SetParent(Transform* transform) { parent = transform; }
    void SetPivot(Vector3 pivot) { this->pivot = pivot; }
    void SetTag(string tag) { this->tag = tag; }
    void SetWorld(Matrix world) { this->world = world; }

    Vector3 GetRight() const { return right.GetNormalized(); }
    Vector3 GetLeft() const { return -right.GetNormalized(); }
    Vector3 GetUp() const { return up.GetNormalized(); }
    Vector3 GetDown() const { return -up.GetNormalized(); }
    Vector3 GetForward() const { return forward.GetNormalized(); }
    Vector3 GetBack() const { return -forward.GetNormalized(); }

    void SetActive(bool isActive) { this->isActive = isActive; }

protected:
    string tag;
    bool isActive = true;

    Vector3 localPosition;
    Vector3 localRotation;
    Vector3 localScale = { 1, 1, 1 };

    Matrix world;

private:
    Transform* parent = nullptr;

    Vector3 pivot;

    Vector3 right, up, forward;
    Vector3 globalPosition, globalRotation, globalScale;

    Float4x4 matWorld;
};