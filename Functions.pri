defineTest(copyFiles) {
    filesToCopy = $$1
    dirToCopy   = $$2

    mkdirCommand = $$QMAKE_MKDIR $$dirToCopy
    copyCommand  = $$QMAKE_COPY $$filesToCopy $$dirToCopy

    QMAKE_POST_LINK += $$mkdirCommand $$escape_expand(\\n\\t) $$copyCommand $$escape_expand(\\n\\t)

    export(QMAKE_POST_LINK)
}

defineTest(copyDir) {
    dirToCopy  = $$1
    dirToPaste = $$2

    mkdirCommand = $$QMAKE_MKDIR $$dirToPaste
    copyCommand  = $$QMAKE_COPY_DIR $$dirToCopy $$dirToPaste

    QMAKE_POST_LINK += $$mkdirCommand $$escape_expand(\\n\\t) $$copyCommand $$escape_expand(\\n\\t)

    export(QMAKE_POST_LINK)
}
