TEMPLATE = app
TARGET = TPDatosFinal
QT += core \
    gui
HEADERS += DialogHelp.h \
    lib/libspopc.h \
    src.datos.classification/Classification.h \
    src.datos.compression/BitInput.h \
    src.datos.compression/BitOutput.h \
    src.datos.compression/BitOutputStream.h \
    src.datos.compression/CompressionManager.h \
    src.datos.consultations/Consultation.h \
    src.datos.consultations/Search.h \
    src.datos.controller/Controller.h \
    src.datos.controller/IndexController.h \
    src.datos.controller/ManagerInvertedIndex.h \
    src.datos.controller/StorageController.h \
    src.datos.controller/gmail-poptest.h \
    src.datos.cryptography/Encryption.h \
    src.datos.cryptography/GaussJordan.h \
    src.datos.cryptography/Hill.h \
    src.datos.exception/eCompression.h \
    src.datos.exception/eExist.h \
    src.datos.exception/eFile.h \
    src.datos.exception/eLostReg.h \
    src.datos.exception/eNotExist.h \
    src.datos.exception/eNotSpace.h \
    src.datos.models/Block.h \
    src.datos.models/CompressedBlock.h \
    src.datos.models/FactoryOfRegistry.h \
    src.datos.models/IndexConfig.h \
    src.datos.models/InfoPerDoc.h \
    src.datos.models/Key.h \
    src.datos.models/KeyInteger.h \
    src.datos.models/KeyString.h \
    src.datos.models/Mail.h \
    src.datos.models/RegClassification.h \
    src.datos.models/RegInvertedIndex.h \
    src.datos.models/RegPrimary.h \
    src.datos.models/RegSelection.h \
    src.datos.models/Registry.h \
    src.datos.models/WordsContainer.h \
    src.datos.storage/BinaryFile.h \
    src.datos.storage/BitArrayBufferCompression.h \
    src.datos.storage/Buffer.h \
    src.datos.storage/File.h \
    src.datos.storage/FreeBlockController.h \
    src.datos.storage/TextFile.h \
    src.datos.test/TestBSharp.h \
    src.datos.test/TestCompression.h \
    src.datos.test/TestCriptography.h \
    src.datos.test/TestManagerInvertedIndex.h \
    src.datos.test/TestStorage.h \
    src.datos.test/TestStorageController.h \
    src.datos.utils/Define.h \
    src.datos.utils/StringUtils.h \
    src.datos.BTreeSharp/BlockDataManager.h \
    src.datos.BTreeSharp/ContainerInsertDataBlock.h \
    src.datos.BTreeSharp/ContainerInsertion.h \
    src.datos.BTreeSharp/IndexBSharp.h \
    src.datos.BTreeSharp/InternalNode.h \
    src.datos.BTreeSharp/IteratorBSharp.h \
    src.datos.BTreeSharp/LeafNode.h \
    src.datos.BTreeSharp/Node.h \
    dialog.h \
    dialogMail.h \
    tpdatosfinal.h
SOURCES += DialogHelp.cpp \
    src.datos.interface/Console.cpp \
    src.datos.classification/Classification.cpp \
    src.datos.compression/BitInput.cpp \
    src.datos.compression/BitOutput.cpp \
    src.datos.compression/BitOutputStream.cpp \
    src.datos.compression/CompressionManager.cpp \
    src.datos.consultations/Consultation.cpp \
    src.datos.consultations/Search.cpp \
    src.datos.controller/Controller.cpp \
    src.datos.controller/IndexController.cpp \
    src.datos.controller/ManagerInvertedIndex.cpp \
    src.datos.controller/StorageController.cpp \
    src.datos.controller/gmail-poptest.cpp \
    src.datos.controller/runApp.cpp \
    src.datos.cryptography/Encryption.cpp \
    src.datos.cryptography/GaussJordan.cpp \
    src.datos.cryptography/Hill.cpp \
    src.datos.models/Block.cpp \
    src.datos.models/CompressedBlock.cpp \
    src.datos.models/FactoryOfRegistry.cpp \
    src.datos.models/IndexConfig.cpp \
    src.datos.models/InfoPerDoc.cpp \
    src.datos.models/Key.cpp \
    src.datos.models/KeyInteger.cpp \
    src.datos.models/KeyString.cpp \
    src.datos.models/Mail.cpp \
    src.datos.models/RegClassification.cpp \
    src.datos.models/RegInvertedIndex.cpp \
    src.datos.models/RegPrimary.cpp \
    src.datos.models/RegSelection.cpp \
    src.datos.models/Registry.cpp \
    src.datos.models/WordsContainer.cpp \
    src.datos.storage/BinaryFile.cpp \
    src.datos.storage/BitArrayBufferCompression.cpp \
    src.datos.storage/Buffer.cpp \
    src.datos.storage/File.cpp \
    src.datos.storage/FreeBlockController.cpp \
    src.datos.storage/TextFile.cpp \
    src.datos.test/MainTest.cpp \
    src.datos.test/TestBSharp.cpp \
    src.datos.test/TestCompression.cpp \
    src.datos.test/TestCriptography.cpp \
    src.datos.test/TestManagerInvertedIndex.cpp \
    src.datos.test/TestStorage.cpp \
    src.datos.test/TestStorageController.cpp \
    src.datos.utils/StringUtils.cpp \
    src.datos.BTreeSharp/BlockDataManager.cpp \
    src.datos.BTreeSharp/ContainerInsertDataBlock.cpp \
    src.datos.BTreeSharp/ContainerInsertion.cpp \
    src.datos.BTreeSharp/IndexBSharp.cpp \
    src.datos.BTreeSharp/InternalNode.cpp \
    src.datos.BTreeSharp/IteratorBSharp.cpp \
    src.datos.BTreeSharp/LeafNode.cpp \
    src.datos.BTreeSharp/Node.cpp \
    dialog.cpp \
    dialogMail.cpp \
    main.cpp \
    tpdatosfinal.cpp
FORMS += tpdatosfinal.ui
RESOURCES += 
