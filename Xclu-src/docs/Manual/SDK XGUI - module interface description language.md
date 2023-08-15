## General information about XGUI
XGUI is a language for describing the module interface, in which module variables are set, provided with settings for their visual display to the user, for example, pagination (Tabs), separators, and a button for choosing file or folder for a string variable.
 
The module interface is stored in the module folder in the `description.xgui` file.
It can be exported to a `.h` file, see https://forum.xclu.dev/t/export-modules-xgui-interface-as-h-file/38.

#### File syntax
The file consists of two parts - a description of the module and a description of its interface elements:
The interface description file consists of the description of the module properties and then the interface elements.

Example:

    #Module -------------------------------------- 
    module_description=Execute external file.
    module_version=1.01 
    module_impl=C++
    #GUI -------------------------------------- 
    page Main 
        //General settings. 
    in float Value value=0 0:1 100,10 
        //Input value.

Leading and trailing spaces on each line are ignored, so you can adjust the indentation as you see fit.

#### Comments
Comments are specified using the `#` character at the beginning of a line (comments in the middle of a line are not supported), for example:

    #Module --------------------------------------
means a comment line.

#### Editing and debugging the module interface
To edit xgui files, you can use the **NotePad++** program by loading the settings for highlighting xgui from `docs/NotePadPP_XGUI.xml`.

To debug the interface of the module being created - call the *Developer - Test module interface ...* menu. It allows you to load the `xgui` file and reload it into the window without restarting Xclu. This allows you to interactively edit the GUI of modules and speeds up the development of new modules.
Namely, you can edit the text of the XGUI file in NotePad++ and then press the *Reload* button.
 
## Description of module properties
At the beginning of the file there is a description of the module in the form of records:

`module_description = Execute external file.` - description that will appear in the add module dialog

`module_version=1.01`

`module_impl=C++`        - type of module connection:
* `C ++` - built-in, C ++
* `JS` - JavaScript code
* `dylib` - DLL
* `python` - Python code


`module_class=Execute` - optional, module class. Attention: you do not need to specify it in built-in modules, since it will be calculated by the folder name.

`module_name_hint=Exec` - optional, name for the module, if not - used `module_class` (and added a number).
 
`module_category=System` - module category. Attention: in built-in modules
                                                        you do not need to specify it, since it will be calculated
                                                        by folder name

## Callbacks requests
Module can request some data from other modules, it's  is determined by the property
```
module_send_calls=create_widget,sound_buffer_add,sound_buffer_received

#* - means no restrictions

```

## Callbacks receiving

Module can answer to callbacks from other modules,
```
module_accept_calls=create_widget,sound_buffer_add,sound_buffer_received
*  - means no restrictions.
```

In this case module must implement corresponding virtual function:
```    
     create_widget()
     on_sound_buffer_add()
     on_sound_buffer_received()
```

## Описание элементов интерфейса 

После свойств модуля идет описание страниц интерфейса. 
Он описывается в файле `xgui` как  набор последовательных инструкций по созданию страниц, сепараторов и переменных. Также, там содержатся инструкции по настройке видимости одних элементов в зависимости от значений других элементов.

Интерфейс состоит из страниц с расположенными на них элементами интерфейса:
* `page`
* `separator`, `line`
* `checkbox`, `group`
* `float`
* `int`
* `checkbox`
* `string`, `string_file`, `string_folder`, (not implemented `string_link_...`) 
* `enum`
* `text`
* `object`
* (not implemented `array_...`, `soundbuffer_...`, `raster_u8c3`, `raster_u8`, `raster_float`, `raster_vec2`, `raster_vec3`, `raster_int2`)
 
Также, могут встречаться директивы условной видимости элементов
    
    if value1 1
    ...
    endif


Первую страницу требуется создать обязательно в самом начале объявления интерфейса. 

Последняя страница *Control* с элементами включения модуля и отслеживания ошибок создается автоматически, а также там `id` модуля. Описание этой сттаницы хранится в файле `general_page.xgui`. 

### Значение символа подчерка в названии типа 
`string_file` - означает, что тип переменной - string, но с дополнительным аттрибутом "file" - это значит, что это строка с именем файла. И визуально для такое переменной добавляется кнопка выбора имени файла. 

`separator_line` - это `separator` с опцией `line`, для краткости можно использовать просто `line`.
`checkbox_group` - это `checkbox` с опцией `group`, для краткости можно использовать просто `group`.


### Пример описания переменной `float`
Пример, как описывается переменная типа float: 

    in float Value_1 value1=0 0:1 0.01,0.1 
        //This is value. 
Здесь:
* `in` - квалификатор, могут быть `in`, `out`, `const`, см. ниже.

* `float` - тип, может быть `int`, `float`, `string`, `enum`, `text`, `button`, `checkbox`, `page`, `separator` 

* `Value` - заголовок в интерфейсе, при показе подчерки заменяются на пробелы, то есть буде показываться как *Value 1*.

* `value1` - внутреннее имя переменной, используемое при программировании. 

* `//This is value` - описание переменной, оно показывается в подсказках, если навести мышь на этот элемент в интерфейсе Xgui. (В этой подсказке покажется и внутреннее имя переменной.)  

* `0 0:1 0.01,0.1` - указывает значение по умолчанию '0',  значение по умолчанию от `0` до `1` (если не требуется задавать, то указывать `*`, например, `0:*` означает, что переменная больше либо равна `0`, и в конце - размер маленьких и больших шагов при изменении переменной. 

В некоторых случаях строк `//` может быть несколько - это дополнительные описания переменной, например, в `string` для задания диалогов выбора файла или папки, или значение по умолчанию для текста. 
Для удобства чтения делается отступ `//` от края, четырьмя пробелами. 

Ниже будет рассказано подробно про все типы элементов интерфейса.
  

## Квалификаторы `in`, `out`, `const`

Квалификаторы обозначают, какой режим работы у переменной. 
Они должны ставиться перед всеми переменными, кроме `page` и `separator`.

* `in` - входной параметр 

* `out` - выходной параметр (модуль может его менять и читать), но пользователь не может его менять.

* `out(save)` - это знак, что значение переменной следует сохранять записывать в файл проекта. По умолчанию, переменные out не сохраняются. 

* `const` - константа, то есть величина, которая не меняется во время выполнения программы. Ее значение можно менять только до запуска. Такие переменные удобны при задании параметров подключения к устройствам - типа разрешения камеры. То, что это константа, позволяет не беспокоиться о том, что пользователь сменит значение во время работы.

#### Как показываются квалификаторы в GUI
* in – обычно
* const - жирным 
* out - подчеркнуто 


## Комментарии 

    #….... 

 
## Элементы оформления - `page`, `separator`, `group`
 
Страницы, сепараторы и групповые чекбоксы служат для разделения блоков переменных на блоки для удобства восприятия программистом.

### Страница `page`
    #------------------------------------------ 
    page Main - новая страница  
        //описание ее (для Help) 
    #------------------------------------------ 
Имя может содержать подчеркивания - они при показе конвертируются в пробелы. 

Обычно страницы отчеркиваются комментарием `#------------------------------------------` для удобства чтения файла `xgui`. 


### Сепараторы `separator`, `line`

`separator`   - вертикальный отступ для отделения групп элементов
`line` - горизонтальная полоска для отделения элементов интерфейса. Сокращение от `separator_line`.

Оба эти элемента внутри представляются как сепараторы. Им назначается имя `__separatorXXX`, где `XXX` - некоторое число. Поэтому, такие имена не следует использовать в программе. 
 
### Группа `group`

Группа `group` - сокращение от `checkbox_group`. Представляет собой `checkbox`, который расположен слева. Его удобно использовать для создания групп элементов, которые показываются только при включенном флажке. 

Типичное использование:

    line
    int group Show_Details show_details=1
        //Group with details.
    if show_details 1
      in int Value1 value1=0 0:10 1,10
      in int Value2 value2=0 0:10 1,10
    endif
    line
    
В этом примере флажок "Show Details" очерчен сверху и снизу линиями. Если он включен - то показываются элементы "Value1" и "Value2". 

Здесь использован условный показ элементов `if...endif`, смотрите про него ниже.

## Условие для показа - if ... endif

    #-------------------- 
    if mode 2 
    ...
    if mode 3,4 
    ... 
    endif 
    #-------------------- 

Внутри `if..if..endif` стоят переменные - они показываются, если переменная (в примере это mode) равна одному значению из списка, и сама включена. 

1) Переменные должны идти по порядку, то есть `mode` должна быть объявлена раньше условия. 

2) Вложенные `if` не поддерживаются, но, по факту, так как скрытие родительского элемента влечет скрытие детей - то имеющийся механизм в каком-то смысле даже более лаконичный. 

3) Чтобы блок с `if` было лучше видно в тексте описания интерфейса, рекомендуем помечать его комментарием `#--------------------` в начале и конце. 

4) В текущей реализации `separator` и `checkbox(group)` - не скрываются, поэтому, не следует делать вложенные `if` с их участием. 

Пример:
    
    line
    int enum Variants variants=A [A,B,C]
        //Variants
    if variants A,B
    #note here that used "A or B" in condition
      in int Value1 value1=0 0:10 1,10
      in int Value2 value2=0 0:10 1,10
    endif
    if variants B
      in int Value3 value3=0 0:10 1,10
    endif
    if variants C
      in int Value4 value4=0 0:10 1,10
    endif
    line

## Скаляры 

### Вещественная переменная `float`
    in float Freq freq=0 0:100 0.1,1  - квалиф., тип, загол., имя, умолч., диапазон, размер шагов
    //Frequency.              - описание 
    //0..100 Hz   - опционально, диапазон и/или единица измерения, показывается справа 

* Первое имя - "title", для показа,  
второе - имя для референса в программировании. 
В title символы подчеркивания заменяются на пробелы, поэтому будет “Q Q”. 

* `0 0:100 0.1,1` - указывает значение по умолчанию ‘0’, диапазон от `0` до `100` 
* Если не требуется задавать границу диапазона, то указывать `*` , например, `0:*` означает, что переменная больше либо равна `0`. 
* Если обе границы - числа (не `*`), то появляется слайдер для быстрой регулировки.
* Два последних параметра в конце, разделенные запятыми - размер маленьких и больших шагов при изменении переменной.



### Целочисленная переменная `int`
    in int A a=0 0:10 1,10 - квалиф., тип, загол., имя, умолч., диапазон, размеры шагов  
    //Number of items.   - описание 
    //0..10 items  - опционально, диапазон и/или единица измерения, показывается справа 

* `0 0:10 100,10` - сначала значение по умолчанию ‘0’, 
* Затем диапазон от `0` до `10`. Если не требуется задавать, то указывать `*` , например, `0:*` означает, что переменная больше либо равна `0`. 
* Если обе границы - числа (не `*`), то появляется слайдер для быстрой регулировки.
* В конце - маленький и большой шаг при изменении переменной, разделенные запятой.

#### Варианты со слайдерами 
*(Не реализовано)*

    in float_slider …  

    in int_slider … 


### Строка `string`

    in string Name name="aa"   - заголовок, имя и значение по умолчанию
       //Name of the object.       - описание

Примечание: значение по умолчанию считывается между первой и последней кавычкой, которые берутся после символа '=', поэтому, можно писать произвольный текст внутри, например, `"this is "a" table"` будет интерпретироваться правильно, как `this is "a" table`.

#### Строка с кнопкой для выбора файла 

    in string_file Name name="aa" 
    //File to load - обычное описание 
    //Choose a file - заголовок диалога 
    //All files (*.*);;Images (*.png *.xpm *.jpg);;Text files (*.txt) - фильтр


#### Строка с кнопкой для выбора папки 

    in string_folder Name name="aa"  
    //Folder to scan - обычное описание 
    //Choose a file - заголовок диалога 


#### Строка выбора переменной заданного типа 
*(В данный момент не реализовано)*

    … string_link_int
    … string_link_image 

Например: `in string_link_int Int_Link int_link="module1->value"` 


### Текст `text`

    in text Text1 text 7 20 
    //Description - описание 
    //"default text"   
    //"…..."   


Многострочный редактор текста, `7 20` - минимальное и максимальное число строк  на экране (lines count). Если какое-то число равно `-1`, это значит, что нет данного ограничения *(Планируется `*` вместо `-1`)*. 

Строки описания - сначала обычная, а затем идут, опционально, дополнительные строки - это текст для значения по-умолчанию, в виде строк, ограниченных " " - чтобы триммер строк не съел пробелы в конце. 

*(Не реализовано)* При этом, добавить к `text` - опцию `text(call:add_sound_buffer)` - тогда появится кнопка для добавления модуля, который понимает эти функции на вход. 
 

### Чекбокс `checkbox`
Простой чекбокс:

    in checkbox Active active=0  
        //This is checkbox.

Показ чекбокса слева с горизонтальной линией, для обозначения коллапсируемой группы элементов: 
    
    in checkbox_group Details_>> show_details=0   
        //This is a group of elements.
 

### Кнопка `button`

    in button Execute execute 
        //This is a button - works at runtime only.

    in button_always Print_Devices print_devices
        //This is a button - works always, at runtime and at editing too.

Кнопка не может иметь квалификатор `out`. 

Сигнал о нажатии кнопок посылается в модули даже в режиме редактирования проекта, но есть не запущенного.  Например, это позволяет выдать список подключенных камер или Arduino до реального запуска.
При этом, если проект не запущен, то значения из GUI отправляются в переменные, отрабатывается нажатие кнопки, а затем значения переменных ставятся в GUI.

### Список `enum`
Combo-box, состоящий из списка заданных элементов. 

     in enum List list=Use_int [Use_int,Use_float]   
     //Number of items                описание 
     //items                    опционально - единица измерения, показывается справа 

* Здесь Use_int - значение по умолчанию и в [..] - список значений.
* Но фактически, значения этого элемента int - индекс выбранного значения, то есть Use_int соответствует 0, а Use_float соответствует 1, и так далее.
* При записи в json записывается `rawtext` - то есть текст "Use_int".
* При показе вариантов подчеркивания преобразуются в строки, то есть на экране будет показано "Use int", "Use float".
* geti этого элемента дает индекс, gets - также индекс, но в строковом виде, а для доступа к текстам - getraw - дает "сырой текст" с подчеркиваниями, и "get_value_title" - без подчеркиваний, а с пробелами.

 
*(Не реализовано)*
Доступ при программировании (в линках): 
`list.title`   - текущая строка с пробелами 
`list.index` - выбранный номер, начиная от 0 
`list.raw` - строка с подчеркиваниями 

 

## Объекты 

### array
Массив. in/const - значит всегда, что это линк.

    in array*     - универсальный массив     
    in array_1d_float     - то есть размерность и тип
* 1d, 2d, 3d 
* int8, uint8, int16, uint16, int=int32, uint32, float, float64 

### raster_
Растровое изображение, различных типов: 

`raster_u8`    
`raster_u8c3`
`raster_s8`  
`raster_int16`   
`raster_u16`   
`raster_u32`     
`raster_int32`  
`raster_float` 
`raster_double`
`raster_vec2`
`raster_vec3`   
`raster_int2` 

`in` или `const` - значит, что это линк.
    
### soundbuffer
Звуковой буфер. Содержит поля sample_rate, channels, size. in/const - значит всегда, что это линк.
    in image*     - универсальный буфер   
    in sound_buffer_float 

* int8, uint8, int16, uint16, int=int32, uint32, float, float64 



### `object`
Объект - точнее, произвольная структура.

    in object Object_To_Save obj_to_save 
        //Object for saving. 

`object_image` - указывает, что ожидается тип изображения.
`object_soundformat` - формат звукового буфера. 
Не реализовано: `object_array`, `object_strings`, `object_json` 

Вообще, типы в скобках могут быть любыми, даже не зарегистрированными - они используются для фильтров при связке переменных.