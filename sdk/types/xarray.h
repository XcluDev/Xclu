#ifndef XARRAY_H
#define XARRAY_H

//1-dimensional array

#include "incl_h.h"

//Array type
class XArray {
public:
    XArray();

    //тип данных
    XTypeId data_type() const;

    //размер массива
    bool is_empty() const;
    unsigned int size() const;    //число элементов
    unsigned int size_bytes() const;  //размер массива в байтах
    unsigned int elem_size() const;    //размер одного элемента

    //выделение памяти и очистка
    void clear();
    void allocate(unsigned int size, XTypeId data_type);

    //получение ссылки на элемент массива
    void *item_pointer(qint32 index);
    void const *item_pointer(qint32 index) const;

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

    quint16* data_uint16();
    quint16 const* data_uint16() const;

    qint32* data_int32();
    qint32 const* data_int32() const;

    quint32* data_uint32();
    quint32 const* data_uint32() const;

    float* data_float();
    float const* data_float() const;

    double* data_double();
    double const* data_double() const;
protected:
    XTypeId data_type_ = XTypeId_none;
    QVector<quint8> data_;    //данные
    quint8 *data_ptr_ = nullptr;    //указатель на данные в data_

    //размер в элементах и байтах
    quint32 size_ = 0;
    quint32 size_bytes_ = 0;
    quint32 elem_size_ = 0; //размер одного элемента

};

#endif // XARRAY_H
