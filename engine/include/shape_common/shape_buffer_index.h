#ifndef MY_PROJECT_SHAPE_BUFFER_INDEX_H
#define MY_PROJECT_SHAPE_BUFFER_INDEX_H
#include <iostream>
class ShapeBufferIndex {
protected:

    size_t	m_PositionDataIndex;
    size_t	m_IndexDataIndex;
    size_t	m_NormalDataIndex;
    size_t	m_TexCoordDataIndex;
    size_t	m_ColorDataIndex;
public:

    ShapeBufferIndex() : m_PositionDataIndex(-1), m_IndexDataIndex(-1), m_NormalDataIndex(-1), m_TexCoordDataIndex(-1), m_ColorDataIndex(-1) {}

    inline size_t GetPositionDataIndex() const { return this->m_PositionDataIndex; }

    inline size_t GetIndexDataIndex() const { return this->m_IndexDataIndex; }

    inline size_t GetNormalDataIndex() const { return this->m_NormalDataIndex; }

    inline size_t GetTexCoordDataIndex() const { return this->m_TexCoordDataIndex; }

    inline size_t GetColorDataIndex() const { return this->m_ColorDataIndex; }

};
#endif //MY_PROJECT_SHAPE_BUFFER_INDEX_H
