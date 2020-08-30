#ifndef XCLUARRAY_H
#define XCLUARRAY_H

//Числовой массив

#include "incl_h.h"

//типы данных в массиве
enum XcluArrayDataType : int {
    XcluArrayDataType_none = 0,
    XcluArrayDataType_u8bit = 1,
    XcluArrayDataType_s8bit = 2,
    XcluArrayDataType_int16 = 3,
    XcluArrayDataType_uint16 = 4,
    XcluArrayDataType_int32 = 5,
    XcluArrayDataType_uint32 = 6,
    XcluArrayDataType_float = 7,
    XcluArrayDataType_double = 8,
    XcluArrayDataType_N = 9
};

//размер одного элемента данных
unsigned int XcluArrayDataTypeSize(XcluArrayDataType type);
QString XcluArrayDataType_to_string(XcluArrayDataType type);
XcluArrayDataType string_to_XcluArrayDataType(QString type);
bool is_XcluArrayDataType_integer(XcluArrayDataType type);
bool is_XcluArrayDataType_float(XcluArrayDataType type);


//Массив
//Важно, что у изображений перечисление размерности идет так: channels, w, h
class XcluArray
{
public:
    XcluArray();

    //тип данных
    XcluArrayDataType data_type() const;

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
    void allocate(QVector<unsigned int> dim, XcluArrayDataType data_type);
    void allocate_1d(unsigned int size, XcluArrayDataType data_type);
    void allocate_image(int channels, int w, int h, XcluArrayDataType data_type);

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

    int get_int(qint32 index) const;
    void set_int(qint32 index, int v);
    float get_float(qint32 index) const;
    void set_float(qint32 index, float v);
    double get_double(qint32 index) const;
    void set_double(qint32 index, double v);

    int get_int(const QVector<quint32> &index) const { return get_int(to_index(index)); }
    void set_int(const QVector<quint32> &index, int v) { set_int(to_index(index), v); }
    float get_float(const QVector<quint32> &index) const { return get_float(to_index(index)); }
    void set_float(const QVector<quint32> &index, int v) { set_float(to_index(index), v); }
    double get_double(const QVector<quint32> &index) const { return get_double(to_index(index)); }
    void set_double(const QVector<quint32> &index, int v) { set_double(to_index(index), v); }

    //получение массивов данных для быстрой работы
    //если size_bytes_ == 0, возвращает nullptr    
    void* data();
    void const* data() const;

    quint8* data_u8bit();
    quint8 const* data_u8bit() const;

    qint8* data_s8bit();
    qint8 const* data_s8bit() const;

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
    XcluArrayDataType data_type_ = XcluArrayDataType_none;
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

#endif // XCLUARRAY_H
