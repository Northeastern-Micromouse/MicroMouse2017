pipeline {
    agent any
    stages {
        stage('Setup') {
            steps {
                echo 'Running ${env.BUILD_ID} on ${env.JENKINS_URL}'
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '3004dcb7-f66a-4e59-a2d3-6c3da31186ff', url: 'https://github.com/Northeastern-Micromouse/MicroMouse2017.git']]])
                sh 'rm -rf builds'
                sh 'mkdir builds'
                sh 'bazel clean'
            }
        }

        stage('Build') {
            steps {
                sh 'echo build'
                notifyBuild()
                sh 'bazel build src/main/cc/...'
            }
        }

        stage('Test') {
            steps {
                sh 'echo test'
                sh 'bazel test src/test/cc/... > builds/output.bazel' // Run the tests.
            }
        }
    }
    post {
        always {
            sh 'echo report'
            sh 'cat builds/output.bazel'
            notifyBuild(currentBuild.result)
        }
    }
}

def notifyBuild(String buildStatus = 'STARTED') {
    // build status of null means successful
    buildStatus =  buildStatus ?: 'SUCCESSFUL'

    // Default values
    def colorName = 'RED'
    def colorCode = '#FF0000'
    def subject = "${buildStatus}: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'"
    def summary = "${subject} (${env.BUILD_URL})"
    def details = """<p>STARTED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]':</p>
      <p>Check console output at &QUOT;<a href='${env.BUILD_URL}'>${env.JOB_NAME} [${env.BUILD_NUMBER}]</a>&QUOT;</p>"""

    // Override default values based on build status
    if (buildStatus == 'STARTED') {
        color = 'YELLOW'
        colorCode = '#FFFF00'
    } else if (buildStatus == 'SUCCESSFUL') {
        color = 'GREEN'
        colorCode = '#00FF00'
    } else {
        color = 'RED'
        colorCode = '#FF0000'
    }

    // Send notifications
    slackSend (color: colorCode, message: summary)
}
