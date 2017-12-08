/****************************************************************************
** Meta object code from reading C++ file 'GuiManager.h'
**
** Created: Thu Dec 7 14:58:08 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GuiManager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuiManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GuiManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      32,   11,   11,   11, 0x08,
      53,   11,   11,   11, 0x08,
      79,   11,   11,   11, 0x08,
      95,   11,   11,   11, 0x08,
     107,   11,   11,   11, 0x08,
     127,  120,   11,   11, 0x08,
     166,  120,   11,   11, 0x08,
     205,  120,   11,   11, 0x08,
     249,  241,   11,   11, 0x08,
     311,  284,   11,   11, 0x08,
     356,  354,   11,   11, 0x08,
     403,  354,   11,   11, 0x08,
     450,  354,   11,   11, 0x08,
     493,   11,   11,   11, 0x08,
     513,   11,   11,   11, 0x08,
     533,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GuiManager[] = {
    "GuiManager\0\0CreateCubeInScene()\0"
    "CreatePlaneInScene()\0CreatePointLightInScene()\0"
    "ImportTexture()\0CreateMat()\0AddPro2Mat()\0"
    "newPos\0setPositionForCurrentObject(glm::vec3)\0"
    "setRotationForCurrentObject(glm::vec3)\0"
    "setScaleForCurrentObject(glm::vec3)\0"
    "matName\0BindMaterialToCurrentObject(char*)\0"
    "PropertyName,PropertyValue\0"
    "BindPropertyToCurrentMaterial(char*,char*)\0"
    ",\0BindPropertyToCurrentMaterial(char*,glm::vec3)\0"
    "BindPropertyToCurrentMaterial(char*,glm::vec2)\0"
    "BindPropertyToCurrentMaterial(char*,float)\0"
    "NextCurrentObject()\0ToggleCastShadows()\0"
    "ToggleReceiveShadows()\0"
};

void GuiManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GuiManager *_t = static_cast<GuiManager *>(_o);
        switch (_id) {
        case 0: _t->CreateCubeInScene(); break;
        case 1: _t->CreatePlaneInScene(); break;
        case 2: _t->CreatePointLightInScene(); break;
        case 3: _t->ImportTexture(); break;
        case 4: _t->CreateMat(); break;
        case 5: _t->AddPro2Mat(); break;
        case 6: _t->setPositionForCurrentObject((*reinterpret_cast< glm::vec3(*)>(_a[1]))); break;
        case 7: _t->setRotationForCurrentObject((*reinterpret_cast< glm::vec3(*)>(_a[1]))); break;
        case 8: _t->setScaleForCurrentObject((*reinterpret_cast< glm::vec3(*)>(_a[1]))); break;
        case 9: _t->BindMaterialToCurrentObject((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 10: _t->BindPropertyToCurrentMaterial((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 11: _t->BindPropertyToCurrentMaterial((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< glm::vec3(*)>(_a[2]))); break;
        case 12: _t->BindPropertyToCurrentMaterial((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< glm::vec2(*)>(_a[2]))); break;
        case 13: _t->BindPropertyToCurrentMaterial((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 14: _t->NextCurrentObject(); break;
        case 15: _t->ToggleCastShadows(); break;
        case 16: _t->ToggleReceiveShadows(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GuiManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GuiManager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GuiManager,
      qt_meta_data_GuiManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GuiManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GuiManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GuiManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GuiManager))
        return static_cast<void*>(const_cast< GuiManager*>(this));
    return QWidget::qt_metacast(_clname);
}

int GuiManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
