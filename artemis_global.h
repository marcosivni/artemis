#ifndef ARTEMIS_GLOBAL_H
#define ARTEMIS_GLOBAL_H

#include <QtCore/qglobal.h>


#if defined(ARTEMIS_LIBRARY)
#  define ARTEMIS_EXPORT Q_DECL_EXPORT
#else
#  define ARTEMIS_EXPORT Q_DECL_IMPORT
#endif

#endif // ARTEMIS_GLOBAL_H
