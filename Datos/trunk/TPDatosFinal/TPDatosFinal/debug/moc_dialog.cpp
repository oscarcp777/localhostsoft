/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created: Sun Nov 28 07:43:14 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Dialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      18,    7,    7,    7, 0x0a,
      32,    7,    7,    7, 0x0a,
      46,    7,    7,    7, 0x0a,
      60,    7,    7,    7, 0x0a,
      71,    7,    7,    7, 0x0a,
      89,    7,    7,    7, 0x0a,
     113,  107,    7,    7, 0x0a,
     138,  107,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Dialog[] = {
    "Dialog\0\0okClick()\0cancelClick()\0"
    "buscarClick()\0borrarClick()\0verClick()\0"
    "resguardarClick()\0configurarClick()\0"
    "texto\0clasificarClick(QString)\0"
    "seleccionarClick(QString)\0"
};

const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog,
      qt_meta_data_Dialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog))
        return static_cast<void*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: okClick(); break;
        case 1: cancelClick(); break;
        case 2: buscarClick(); break;
        case 3: borrarClick(); break;
        case 4: verClick(); break;
        case 5: resguardarClick(); break;
        case 6: configurarClick(); break;
        case 7: clasificarClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: seleccionarClick((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
