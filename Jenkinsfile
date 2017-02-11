#!groovy
node {

	stage 'Test' 
		echo 'Running ${env.BUILD_ID} on ${env.JENKINS_URL}'
		checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '3004dcb7-f66a-4e59-a2d3-6c3da31186ff', url: 'https://github.com/Northeastern-Micromouse/MicroMouse2017.git']]])
		stage 'Report'
		sh 'rm -rf builds'
		sh 'mkdir builds'
		sh 'bazel clean'
		sh 'bazel test src/test/cc/... > builds/output.bazel'
		echo '-----------------------Build results----------------------------'
		sh 'cat builds/output.bazel'
		notifySuccessful()
}


def notifySuccessful() {
  slackSend (color: '#00FF00', message: "SUCCESSFUL: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]' (${env.BUILD_URL})")
}