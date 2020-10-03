#ifndef XARRAYMULTI_H
#define XARRAYMULTI_H

//Multidimensional array, currently not used

#include "incl_h.h"
#include "xarray.h"


//Multidimensional array
//order of indices: channels, w, h
//TODO make inherited from XArray
class XArrayMulti
{
public:
    XArrayMulti();

    //тип данных
    XTypeId data_type() const;

    //размер массива
    bool is_empty() const;
    const QVector<quint32> &dim() const;
    int dims() const;

    int w() const;
    int h() const;
    int image_channels() const;
    unsigned int size() const;    //число элементов
    unsigned int size_bytes() const;  //размер массива в байтах
    unsigned int elem_size() const;    //размер одного элемента

    //выделение памяти и очистка
    void clear();
    void allocate(QVector<unsigned int> dim, XTypeId data_type);
    void allocate_1d(unsigned int size, XTypeId data_type);
    void allocate_image(int channels, int w, int h, XTypeId data_type);

    //перевести вектор индексов в одномерный индекс
    //TODO почему-то to_index не делается inline
    quint32 to_index(const QVector<quint32> &index_vec) const;
    quint32 pixel_index(int channel, int x, int y) const;
    //получение ссылки на элемент массива
    void *item_pointer(qint32 index);
    void const *item_pointer(qint32 index) const;
    void *pixel_pointer(int x, int y); //для изображений
    void const *pixel_pointer(int x, int y) const; //для изображений

    //работа со значениями
    inline bool is_int()  const;      //это целочисленный массив
    inline bool is_float()  const;    //это массив float
    inline bool is_double()  const;    //это массив double

    void fill(int v);       //заполнить одинаковыми значениями
    void fill(double v);

    int geti(qint32 index) const;
    void seti(qint32 index, int v);
    float getf(qint32 index) const;
    void setf(qint32 index, float v);
    double get_double(qint32 index) const;
    void set_double(qint32 index, double v);

    int geti(const QVector<quint32> &index) const { return geti(to_index(index)); }
    void seti(const QVector<quint32> &index, int v) { seti(to_index(index), v); }
    float getf(const QVector<quint32> &index) const { return getf(to_index(index)); }
    void setf(const QVector<quint32> &index, int v) { setf(to_index(index), v); }
    double get_double(const QVector<quint32> &index) const { return get_double(to_index(index)); }
    void set_double(const QVector<quint32> &index, int v) { set_double(to_index(index), v); }

    //получение массивов данных для быстрой работы
    //если size_bytes_ == 0, возвращает nullptr    
    void* data();
    void const* data() const;

    quint8* data_u8();
    quint8 const* data_u8() const;

    qint8* data_s8();
    qint8 const* data_s8() const;

    qint16* data_int16();
    qint16 const* data_int16() const;

    quint16* data_u16();
    quint16 const* data_u16() const;

    qint32* data_int32();
    qint32 const* data_int32() const;

    quint32* data_u32();
    quint32 const* data_u32() const;

    float* data_float();
    float const* data_float() const;

    double* data_double();
    double const* data_double() const;
protected:
    XTypeId data_type_ = XTypeId_none;
    QVector<quint32> dim_;      //размер по измерениям. Последнее - число каналов для изображений и звуков
    int dims_ = 0;
    QVector<quint8> data_;    //данные
    quint8 *data_ptr_ = nullptr;    //указатель на данные в data_

    //быстрое вычисление индексов
    QVector<quint32> index_mult_;

    //размер в элементах и байтах
    quint32 size_ = 0;
    quint32 size_bytes_ = 0;

    quint32 elem_size_ = 0; //размер одного элемента



};

#endif // XARRAYMULTI_H
