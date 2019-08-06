#!/usr/bin/env groovy

@Library('kanolib')
import build_deb_pkg

stage ('Build') {
    node ('ubuntu_18.04_with_docker') {
        docker.image('kanocomputing/mercury-builder').inside('--cap-add SYS_PTRACE') {
            checkout scm

            parallel(
                'Build - Debug': {
                    sh 'make build-debug'
                },
                'Build - Release': {
                    sh 'make build-release'
                }
            )
        }
    }
}

stage ('Test') {
    node ('ubuntu_18.04_with_docker') {
        docker.image('kanocomputing/mercury-builder').inside('--cap-add SYS_PTRACE') {
            checkout scm

            parallel(
                'C++ Tests': {
                    try {
                        sh 'make test-library'
                    } catch (e) {
                        throw e
                    } finally {
                        xunit (
                            testTimeMargin: '3000',
                            thresholdMode: 1,
                            thresholds: [
                                skipped(failureThreshold: '0'),
                                failed(failureThreshold: '0')
                            ],
                            tools: [
                                CTest(
                                    pattern: 'build/Debug/Testing/**/*.xml',
                                    deleteOutputFiles: true,
                                    failIfNotNew: false,
                                    skipNoTestFiles: true,
                                    stopProcessingIfError: true
                                )
                            ]
                        )
                        publishHTML([
                            allowMissing: true,
                            alwaysLinkToLastBuild: true,
                            keepAll: true,
                            reportDir: 'build/Debug/coverage',
                            reportFiles: 'index.html',
                            reportName: 'Code Coverage',
                            reportTitles: ''
                        ])
                    }
                },
                'Python 3 Tests': {
                    // FIXME: Python dependencies not installed
                    // sh 'make test-python'
                },
                'Python 2 Tests': {
                    // FIXME: Python dependencies not installed
                    // sh 'make test-python2'
                }
            )
        }
    }
}

stage ('Upload Package') {
    /**
     * TODO: Push the build to Conan when pushing to master. Need to resolve
     *       permissions issues with the Conan server.
     *
     * node ('ubuntu_18.04_with_docker') {
     *     docker.image('kanocomputing/mercury-builder').inside() {
     *         sh 'conan upload --remote dev-team --all --confirm "Mercury"
     *     }
     * }
    */

}

stage ('Package') {
    autobuild_repo_pkg 'mercury'
}
