/****************************************************************************
** Meta object code from reading C++ file 'Gui_Property_Manager.h'
**
** Created: Thu Dec 7 14:48:23 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Gui_Property_Manager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Gui_Property_Manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Gui_Property_Manager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   22,   21,   21, 0x05,
      57,   50,   21,   21, 0x05,
      87,   78,   21,   21, 0x05,
     123,  110,   21,   21, 0x05,
     172,  145,   21,   21, 0x05,
     221,  200,   21,   21, 0x05,
     270,  249,   21,   21, 0x05,
     320,  298,   21,   21, 0x05,
     345,   21,   21,   21, 0x05,
     366,   21,   21,   21, 0x05,
     385,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     407,   21,   21,   21, 0x08,
     431,   21,   21,   21, 0x08,
     455,   21,   21,   21, 0x08,
     476,   21,   21,   21, 0x08,
     499,   21,   21,   21, 0x08,
     522,   21,   21,   21, 0x08,
     532,   21,   21,   21, 0x08,
     552,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Gui_Property_Manager[] = {
    "Gui_Property_Manager\0\0newPos\0"
    "ChangePos(glm::vec3)\0newRot\0"
    "ChangeRot(glm::vec3)\0newScale\0"
    "ChangeScale(glm::vec3)\0MaterialName\0"
    "ChangeMaterial(char*)\0PropertyName,PropertyValue\0"
    "ChangeProperty(char*,char*)\0"
    "PropertyName,newVec3\0ChangeVec3(char*,glm::vec3)\0"
    "PropertyName,newVec2\0ChangeVec2(char*,glm::vec2)\0"
    "PropertyName,newFloat\0ChangeFloat(char*,float)\0"
    "SwitchToNextObject()\0ToggleCastShadow()\0"
    "ToggleReceiveShadow()\0PositionButtonClicked()\0"
    "RotationButtonClicked()\0ScaleButtonClicked()\0"
    "BindMatButtonClicked()\0BindPptButtonClicked()\0"
    "NextObj()\0CastShadowChanged()\0"
    "ReceiveShadowChanged()\0"
};

void Gui_Property_Manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Gui_Property_Manager *_t = static_cast<Gui_Property_Manager *>(_o);
        switch (_id) {
        case 0: _t->ChangePos((*reinterpret_cast< glm::vec3(*)>(_a[1]))); break;
        case 1: _t->ChangeRot((*reinterpret_cast< glm::vec3(*)>(_a[1]))); break;
        case 2: _t->ChangeScale((*reinterpret_cast< glm::vec3(*)>(_a[1]))); break;
        case 3: _t->ChangeMaterial((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 4: _t->ChangeProperty((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 5: _t->ChangeVec3((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< glm::vec3(*)>(_a[2]))); break;
        case 6: _t->ChangeVec2((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< glm::vec2(*)>(_a[2]))); break;
        case 7: _t->ChangeFloat((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 8: _t->SwitchToNextObject(); break;
        case 9: _t->ToggleCastShadow(); break;
        case 10: _t->ToggleReceiveShadow(); break;
        case 11: _t->PositionButtonClicked(); break;
        case 12: _t->RotationButtonClicked(); break;
        case 13: _t->ScaleButtonClicked(); break;
        case 14: _t->BindMatButtonClicked(); break;
        case 15: _t->BindPptButtonClicked(); break;
        case 16: _t->NextObj(); break;
        case 17: _t->CastShadowChanged(); break;
        case 18: _t->ReceiveShadowChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Gui_Property_Manager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Gui_Property_Manager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Gui_Property_Manager,
      qt_meta_data_Gui_Property_Manager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Gui_Property_Manager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Gui_Property_Manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Gui_Property_Manager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gui_Property_Manager))
        return static_cast<void*>(const_cast< Gui_Property_Manager*>(this));
    return QWidget::qt_metacast(_clname);
}

int Gui_Property_Manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Gui_Property_Manager::ChangePos(glm::vec3 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Gui_Property_Manager::ChangeRot(glm::vec3 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Gui_Property_Manager::ChangeScale(glm::vec3 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Gui_Property_Manager::ChangeMaterial(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Gui_Property_Manager::ChangeProperty(char * _t1, char * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Gui_Property_Manager::ChangeVec3(char * _t1, glm::vec3 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Gui_Property_Manager::ChangeVec2(char * _t1, glm::vec2 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Gui_Property_Manager::ChangeFloat(char * _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Gui_Property_Manager::SwitchToNextObject()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Gui_Property_Manager::ToggleCastShadow()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void Gui_Property_Manager::ToggleReceiveShadow()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
