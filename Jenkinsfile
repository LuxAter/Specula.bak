pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        cmakeBuild buildType: 'Debug', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true]]
      }
    }
    stage('Test') {
      steps {
        ctest 'InSearchPath'
      }
    }
    stage('Analyse') {
      steps {
        sh label: '', returnStatus: true script: 'cppcheck . --xml --language=c++ 2> cppcheck-result.xml'
        publishCppcheck allowNoReport: true, ignoreBlankFiles: true, pattern: '**/cppcheck-result.xml'
      }
    }
  }
}
