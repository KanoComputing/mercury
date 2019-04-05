#!groovy

pipeline {
    agent {
        label 'ubuntu_18.04_with_docker'
    }

    stages {
        stage('Build, test and document') {
            parallel {
                stage('Test') {
                    steps {
                        script {
                            docker.image('slaves/cmake').inside {
                                sh 'make test'
                            }
                        }
                    }
                }


                stage('Documentation') {
                    // when {
                    //     branch 'master'
                    // }
                    steps {
                        script {
                            docker.image('kanocomputing/docs-builder:latest').inside {
                                sh 'make docs'
                            }
                        }

                    }
                }
            }
        }
    }
}
