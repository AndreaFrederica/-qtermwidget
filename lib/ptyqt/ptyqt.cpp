#include "ptyqt.h"
#include <utility>

#ifdef Q_OS_WIN
#include "conptyprocess.h"

IPtyProcess *PtyQt::createPtyProcess(IPtyProcess::PtyType ptyType) {
    Q_UNUSED(ptyType);
    return new ConPtyProcess();
}
#endif

#ifdef Q_OS_UNIX

#include "unixptyprocess.h"

IPtyProcess *PtyQt::createPtyProcess(IPtyProcess::PtyType ptyType) {
    Q_UNUSED(ptyType);
    return new UnixPtyProcess();
}

#endif
